// only for esp boards
#include <Arduino.h>
// only for esp boards

#include "sbus.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// initializa sbus library
SbusRx sbus_rx(&Serial);

void setup() {
// cannot use serial, the sbus library is keeping the serial0 busy
// Serial.begin(115200);
  delay(10);
  sbus_rx.Begin();
  // small delay before initializing the lcd to prevent a fail
  delay(100);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    // Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }  
  //display.setRotation(180);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("SBUS TEST");
  display.println("    3");
  display.println(" CHANNELS");
  display.display();

  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // initialize the channel print on the screen
  for(int i=0 ; i<13 ; i++){
    if (i < 7){
      display.setCursor(0, (i + 1) * 10);
      display.print("CH" +  String(i) +"->");
    }
    else{
      display.setCursor(60, (i - 6) * 10);
      display.print("CH" +  String(i) +"->");
    }
  }
  display.display();
}

void loop() {
  // erase the previous channel values received from an sbus TX   
  display.fillRect(30, 0, 30, 64, BLACK);
  display.fillRect(100, 0, 30, 64, BLACK);

  // loop over the channels received from the sbus TX
  if (sbus_rx.Read()) {
   for (int i = 0; i < 13; i++) {
     if (i < 7){
      display.setCursor(30, (i + 1) * 10);     
      display.println(sbus_rx.rx_channels()[i]);
     }
     else{
      display.setCursor(100, (i - 6) * 10);     
      display.println(sbus_rx.rx_channels()[i]);
     }
   }    
  display.display();
  }      
}
