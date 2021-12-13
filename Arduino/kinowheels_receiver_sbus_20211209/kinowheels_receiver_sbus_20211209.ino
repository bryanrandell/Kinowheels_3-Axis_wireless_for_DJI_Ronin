#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <BMC_SBUS.h>
#include "lcd_and_rotary.h"
#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01
BMC_SBUS mySBUS; 

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel
// const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

struct Channels{
  uint16_t Pan;
  uint16_t Tilt;
  uint16_t Roll;
};
Channels channels;

// Declare sbus control channels
uint8_t panChannel = 1;
uint8_t tiltChannel = 2;
uint8_t rollChannel = 4;
// other sbus channel for determining wich is wich  
uint8_t channel_3 = 3, channel_5 = 5, channel_6 = 6;

uint8_t ButtonPushPin = 6;
const uint8_t sbusWAIT = 0;
uint8_t radio_channel; 

extern uint8_t radio_channel_value;
uint8_t previous_radio_channel_value;
unsigned long currentMillis;
unsigned long  previousMillis = 0;
const long sbusInterval = 7;

void setup() {
  // Initialisation du port série (pour afficher les infos reçues, sur le "Moniteur Série" de l'IDE Arduino)
  delay(100);
  lcd_and_rotary_begin();
  // Serial.begin(115200);  
  mySBUS.begin(); 
  delay(100);
  pinMode(ButtonPushPin, INPUT_PULLUP);

  // Partie NRF24
  radio.begin();                      // Initialisation du module NRF24
  radio.setPALevel(RF24_PA_HIGH); // Sélection d'un niveau "MINIMAL" pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.setDataRate(RF24_2MBPS);
  radio.openReadingPipe(1, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
  radio_channel_value = radio.getChannel();
  refresh_lcd_radio_channel_value_lock(radio_channel_value);
  delay(10);
  radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
  
}

void loop() {
  // Serial.println("-----------> ");
  currentMillis = millis();


  if (!lock_channel_LCD && radio_channel_value != previous_radio_channel_value){
    refresh_lcd_radio_channel_value_lock(radio_channel_value);
    radio.setChannel(radio_channel_value);
    
  }
  else if(lock_channel_LCD){
    refresh_lcd_radio_channel_value_unlock(radio_channel_value);
  }
  // else{
  //   refresh_lcd_radio_channel_value_lock(radio_channel_value);
  // }
  // Checkpoint 1
  // Serial.print("checkpoint 1 ---> ");
  // Serial.println(millis() - currentMillis);
  // currentMillis = millis();

  if (digitalRead(ButtonPushPin) == LOW){
    pushButton();    
    refresh_lcd_radio_channel_value_lock(radio_channel_value);
    radio.setChannel(radio_channel_value);
  }
  // On vérifie à chaque boucle si un message est arrivé
  if (radio.available()) {
    
    radio.read(&channels, sizeof(channels));  // Si un message vient d'arriver, on le charge dans la variable "message"
    int panValue = channels.Pan;
    int tiltValue = channels.Tilt;
    int rollValue = channels.Roll;
     
    mySBUS.Servo(panChannel, panValue);
    mySBUS.Servo(tiltChannel, tiltValue);
    mySBUS.Servo(rollChannel, rollValue);
    
    mySBUS.Servo(channel_3, 0);
    mySBUS.Servo(channel_5, 0);
    mySBUS.Servo(channel_6, 0);


    // mySBUS.Update();
    // mySBUS.Send();
    // delay(1);
    
    if (currentMillis - previousMillis >= sbusInterval){ 
      mySBUS.Update();
      mySBUS.Send(); 
      // Serial.print("ButtonPushPin -----> ");
      // Serial.print(digitalRead(ButtonPushPin));
      // Serial.print("lock_channel_LCD -----> ");
      // Serial.print(lock_channel_LCD);
      // Serial.print("PAN -----> ");
      // Serial.print(panValue);
      // Serial.print(" TILT -----> ");
      // Serial.print(tiltValue);
      // Serial.print(" ROLL -----> ");
      // Serial.println(rollValue);
      
    }
    previousMillis = currentMillis;
  }
    // Checkpoint 1
  // Serial.print("checkpoint 2 ---> ");
  // Serial.println(millis() - currentMillis);
  // currentMillis = millis();
  previous_radio_channel_value = radio_channel_value;
}

