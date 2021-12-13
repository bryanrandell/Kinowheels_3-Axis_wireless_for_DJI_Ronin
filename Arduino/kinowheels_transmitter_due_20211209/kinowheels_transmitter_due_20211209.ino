#include "kinowheel_due.h"
#include "lcd_and_rotary.h"

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <BMC_SBUS_DUE.h>

#define pinCE   7 
#define pinCSN  8 
#define tunnel  "PIPE1"  

// using a modified version of the BMC_SBUS library, just using a different serial port for communicating
BMC_SBUS_DUE mySBUS;

RF24 radio(pinCE, pinCSN);

const long sbusInterval = 7;
const uint8_t panChannel = 1, tiltChannel = 2, rollChannel = 4;
// other sbus channels for testing purpose
const uint8_t channel_3 = 3, channel_5 = 5, channel_6 = 6;
// radio variables
const byte adresse[6] = tunnel;
// const byte slaveAddress[5] = {'R','x','A','A','A'};
extern bool radio_activated;

unsigned long previousMillis = 0;
unsigned long currentMillis;
// just for debug purpose
const uint32_t potPinX = 1, potPinY = 2, potPinZ = 3;

// external values from lcd and rotary cpp file
extern uint8_t radio_channel_value;
extern bool lock_channel_LCD;
// variables for kinowheel software
float kino_pulsesX, kino_pulsesY;
float floatMultiplicatorX, floatMultiplicatorY;

// data struct for send via nRF24
struct Channels{
  uint16_t Pan;
  uint16_t Tilt;
  uint16_t Roll;
};
struct Channels channels;

void setup() {
  delay(100);
  lcd_and_rotary_begin();
  //Sbus init
  mySBUS.begin();
  delay(100);
  // radio setup
  radio.begin();                      // Initialisation du module NRF24
  radio.setPALevel(RF24_PA_HIGH);      // Sélection d'un niveau "MINIMAL" pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.setDataRate(RF24_2MBPS);
  radio.setRetries(3,5);
  radio.openWritingPipe(adresse);     // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné

  radio_channel_value = radio.getChannel();
  refresh_lcd_radio_channel_value_lock(radio_channel_value);
  // radio.stopListening();

  kinowheel_begin();
  
  currentMillis = millis();

  //Serial init for using wheels whith the software
  Serial.begin(115200);
  delay(100);
  // Maybe useless
  Serial.print("Connected");
}

void loop() {

  // for timing debug
  // Serial.println("-----------");
  
  // using a boolean value for refreshing the lcd screen, only for speed matter
  if (lock_channel_LCD){
    refresh_lcd_radio_channel_value_unlock(radio_channel_value);
  }
  else{
    refresh_lcd_radio_channel_value_lock(radio_channel_value);
    radio.setChannel(radio_channel_value);
  }
  // // Checkpoint 1
  // Serial.print("checkpoint 1 ---> ");
  // Serial.println(millis() - currentMillis);
  // currentMillis = millis();

  // timing calculator for Sbus
  if (currentMillis - previousMillis >= sbusInterval){ 
    
    channels.Pan = kinowheel_X_value();
    channels.Tilt = kinowheel_Y_value();
    channels.Roll = kinowheel_Z_value();
    kino_pulsesX = kinowheel_pulsesX();
    kino_pulsesY = kinowheel_pulsesY();

    // // Checkpoint 2
    // Serial.print("checkpoint 2 ---> ");
    // Serial.println(millis() - currentMillis);
    // currentMillis = millis();

    // Sbus part
    mySBUS.Servo(panChannel,channels.Pan);
    mySBUS.Servo(tiltChannel,channels.Tilt);
    mySBUS.Servo(rollChannel, channels.Roll);

    // todo be able to modify these values via a button or the main rotary encoder
    mySBUS.Servo(channel_3, 0);
    mySBUS.Servo(channel_5, 0);
    mySBUS.Servo(channel_6, 0);
    
    // // Checkpoint 3
    // Serial.print("checkpoint 3 ---> ");
    // Serial.println(millis() - currentMillis);
    // currentMillis = millis();
    
    // the two methods from the BMC_SBUS library to send the signal to the ronin
    mySBUS.Update();
    mySBUS.Send(); 

    // // Checkpoint 4
    // Serial.print("checkpoint 4 ---> ");
    // Serial.println(millis() - currentMillis);
    // currentMillis = millis();

    // // debug part, checking if we are sending a coherent signal
    // Serial.print(currentMillis - previousMillis);
    // Serial.print(" ----- ");
    // Serial.print(channels.Pan);
    // Serial.print(" --- ");
    // Serial.print(channels.Tilt);
    // Serial.print(" --- ");
    // Serial.print(channels.Roll);
    // Serial.print(" --- ");
    // Serial.print(analogRead(potPinX));
    // Serial.print(" --- ");
    // Serial.print(analogRead(potPinY));
    // Serial.print(" --- ");
    // Serial.print(analogRead(potPinZ));

    previousMillis = currentMillis;

    // currentMillis = millis();

    // Serial.print("--- Is radio sending -- ");
    // Serial.println(radio.available());

  
    bool result;
    result = radio.write(&channels, sizeof(channels));

  // }  
  // Serial.println(result);
  // // Checkpoint 5 
  // Serial.print("checkpoint 5 ---> ");
  // Serial.println(millis() - currentMillis);
  
  }
  currentMillis = millis();

  //the part for the software (Kinowheel) usage  
  if(millis() - previousMillis >= 20){
    Serial.print("x");
    Serial.print(kino_pulsesX);
    Serial.print("y");
    Serial.print(kino_pulsesY);
    Serial.println("end");

    previousMillis = millis();    
  }

}
