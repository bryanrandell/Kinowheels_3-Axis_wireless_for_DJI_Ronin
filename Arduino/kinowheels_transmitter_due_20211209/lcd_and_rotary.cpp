#include <Arduino.h>
#include "lcd_and_rotary.h"

#define BAUDRATE 115200
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define WIRECLKDURING 1000000
#define WIRECLKAFTER 400000
#define DELAY_REBOND_TIME_BUTTON 300
#define DELAY_REBOND_TIME_ROTARY 100

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,OLED_RESET, WIRECLKDURING, WIRECLKAFTER);
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,OLED_RESET);


static const unsigned char PROGMEM image_data_cbc[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xfc, 0x3f, 0xfe, 0x0f, 0xfe, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xfd, 0x0f, 0xfe, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xf4, 0x3f, 0xfd, 0x0f, 0xfd, 0x0f, 0xff, 0xbf, 0xff, 0xfe, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0x8e, 0x7f, 0xf4, 0x9f, 0xf9, 0x8f, 0xff, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0x40, 0x7f, 0xc8, 0x3f, 0xf0, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 
    0x1f, 0xff, 0xfc, 0x80, 0x0f, 0x00, 0x01, 0xc0, 0x0f, 0xf8, 0x01, 0xf9, 0xf8, 0x60, 0x00, 0x00, 
    0x1f, 0xff, 0xfb, 0x07, 0x00, 0x40, 0x00, 0x20, 0x00, 0x60, 0x03, 0xf9, 0xf9, 0x10, 0x00, 0x00, 
    0x1f, 0xff, 0xf6, 0x0f, 0xe1, 0x83, 0xe0, 0x61, 0x80, 0x00, 0x03, 0xf9, 0xf9, 0x88, 0x00, 0x00, 
    0x1f, 0xff, 0xec, 0x1f, 0xfb, 0x07, 0xfc, 0xc3, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 
    0x1f, 0xff, 0xe8, 0x3f, 0xff, 0x0f, 0xfd, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 
    0x1f, 0xff, 0xd0, 0x7f, 0xf6, 0x1f, 0xfa, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 
    0x1f, 0xff, 0xc0, 0x1f, 0xf4, 0x0f, 0xf7, 0x8f, 0xe0, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
    0x1f, 0xff, 0xc0, 0x07, 0xf0, 0x03, 0xf4, 0x07, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x18, 
    0x1f, 0xff, 0x80, 0x07, 0xf0, 0x81, 0xf0, 0x01, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00, 0x7e, 0x10, 
    0x1f, 0xff, 0x87, 0xc7, 0xf1, 0xe1, 0xf0, 0x81, 0x80, 0x3e, 0x20, 0x00, 0x00, 0x03, 0xff, 0xf8, 
    0x1f, 0xff, 0x07, 0x87, 0xc1, 0xe3, 0xf0, 0xf1, 0x80, 0x63, 0x10, 0x00, 0x00, 0x1b, 0x61, 0xb8, 
    0x1f, 0xfc, 0x0f, 0x0f, 0x83, 0xc7, 0xc1, 0xe3, 0x80, 0x99, 0x88, 0x00, 0x00, 0x00, 0xcc, 0xf8, 
    0x1f, 0xf8, 0x3e, 0x1f, 0x0f, 0xc7, 0x83, 0xe7, 0x80, 0xbc, 0xc4, 0x00, 0x00, 0x01, 0x9e, 0xd0, 
    0x1f, 0xf0, 0xfe, 0x3e, 0x3f, 0x8f, 0x07, 0xc7, 0xc1, 0x9c, 0xa3, 0xff, 0xf8, 0x01, 0x9e, 0xc0, 
    0x1f, 0xc3, 0xfc, 0x7c, 0xff, 0x1e, 0x1f, 0xcf, 0xf2, 0xc1, 0xbf, 0xf8, 0x00, 0x00, 0x8c, 0xc0, 
    0x1f, 0x87, 0xf0, 0xf1, 0xfc, 0x38, 0x7f, 0x1f, 0xff, 0x77, 0x7f, 0xf8, 0x00, 0x00, 0xc1, 0x80, 
    0x1f, 0x0f, 0xf8, 0x20, 0x7e, 0x00, 0x7e, 0x0f, 0xff, 0xbc, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0x00, 
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x00, 0x10, 0x00, 0x00, 0x1c, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x03, 0xfe, 0x01, 0xff, 0x07, 0xf0, 0x7f, 0x07, 0xff, 0x07, 0xfc, 0x3f, 0xff, 0x7f, 0x3f, 0xf8, 
    0x07, 0xff, 0x03, 0xff, 0x87, 0xf0, 0x7f, 0x07, 0xff, 0x1f, 0xfe, 0x3f, 0xff, 0x7f, 0x3f, 0xf8, 
    0x0f, 0xff, 0x87, 0xff, 0xc7, 0xf0, 0x7f, 0x07, 0xff, 0x1f, 0xff, 0x3f, 0xff, 0x7f, 0x3f, 0xf8, 
    0x1f, 0xdf, 0xc7, 0xef, 0xe7, 0xf0, 0x7f, 0x07, 0xff, 0x3f, 0xbf, 0x3f, 0xff, 0x7f, 0x3f, 0xf8, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xf0, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0x80, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xe0, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0x80, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xe0, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0x80, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xe0, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0x80, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xfe, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0xf0, 
    0x1f, 0x8e, 0x4f, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xfe, 0x3f, 0x11, 0x03, 0xf0, 0x7f, 0x3f, 0xf8, 
    0x1f, 0x80, 0x0f, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xfe, 0x3f, 0x00, 0x03, 0xf0, 0x7f, 0x3f, 0xf8, 
    0x1f, 0x80, 0x0f, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xfe, 0x3f, 0x00, 0x03, 0xf0, 0x7f, 0x3f, 0xf8, 
    0x1f, 0x80, 0x0f, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xfe, 0x3f, 0x00, 0x03, 0xf0, 0x7f, 0x3f, 0xb0, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xe0, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0x80, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xe0, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0x80, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xf0, 0x7f, 0x07, 0xe0, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0x80, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xf0, 0x7e, 0x07, 0xe0, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0x80, 
    0x1f, 0x8f, 0xcf, 0xe7, 0xe7, 0xff, 0x7f, 0xe7, 0xff, 0x3f, 0x3f, 0x83, 0xf0, 0x7f, 0x3f, 0x80, 
    0x0f, 0xdf, 0xc7, 0xff, 0xc7, 0xff, 0x7f, 0xe7, 0xff, 0x3f, 0xff, 0x03, 0xf0, 0x7f, 0x3f, 0x80, 
    0x0f, 0xff, 0x87, 0xff, 0xc7, 0xff, 0x7f, 0xe7, 0xff, 0x1f, 0xff, 0x03, 0xf0, 0x7f, 0x3f, 0x80, 
    0x07, 0xff, 0x03, 0xff, 0x87, 0xff, 0x7f, 0xf7, 0xff, 0x0f, 0xfe, 0x03, 0xf0, 0x7f, 0x3f, 0x80, 
    0x01, 0xfc, 0x00, 0xfe, 0x03, 0xfe, 0x7f, 0xe7, 0xff, 0x03, 0xf8, 0x03, 0xf0, 0x3f, 0x3f, 0x80, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 
    0x18, 0xc0, 0xc6, 0x06, 0x30, 0x31, 0x80, 0x00, 0xc6, 0x00, 0x60, 0x06, 0x30, 0x31, 0x83, 0xc0, 
    0x18, 0x80, 0xc6, 0x06, 0x30, 0x31, 0x80, 0x00, 0xc0, 0x00, 0xd0, 0x06, 0x30, 0x11, 0x82, 0x80, 
    0x18, 0x80, 0xc6, 0x06, 0x30, 0x31, 0x80, 0x00, 0xc0, 0x01, 0x98, 0x06, 0x30, 0x11, 0x80, 0x80, 
    0x18, 0xc0, 0xc6, 0x06, 0x30, 0x31, 0x80, 0x00, 0xc6, 0x03, 0x0c, 0x06, 0x30, 0x31, 0x80, 0x80, 
    0x10, 0x80, 0x44, 0x02, 0x20, 0x11, 0x00, 0x00, 0x04, 0x06, 0x04, 0x02, 0x20, 0x10, 0x80, 0x80, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };


//pin on the rotary encoder
const int RotaryCLK = 10, RotaryDT = 11, ButtonPushPin = 9; 
//Statuses for the rotary encoder
int CLKNow, CLKPrevious, DTNow, DTPrevious;
bool buttonState = false;
extern bool lock_channel_LCD = false;
int counterPush = 0; 
extern uint8_t radio_channel_value = 0; // in case of double push function
extern bool radio_activated = 1;

// // button push variables
// const int SHORT_PRESS_TIME = 100; // 1000 milliseconds
// const int LONG_PRESS_TIME  = 500; // 1000 milliseconds

// // Variables will change:
// int lastState = LOW;  // the previous state from the input pin
// int currentState;     // the current reading from the input pin
// unsigned long pressedTime  = 0;
// unsigned long releasedTime = 0;
// bool isPressing = false;
// bool isLongDetected = false;

void lcd_and_rotary_begin(){
  // Wire.setClock(400000UL);
  //Serial.begin(BAUDRATE);
  //while (! Serial) delay(100);
  //Serial.println("SSD1306 OLED test");
  // for init the lcd screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  CLKPrevious = digitalRead(RotaryCLK);
  DTPrevious = digitalRead(RotaryDT); 
  attachInterrupt(digitalPinToInterrupt(RotaryCLK), rotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ButtonPushPin), pushButton, INPUT_PULLUP);
  
  // Clear the buffer.
  display.clearDisplay();
  // Draw bitmap on the screen
  display.drawBitmap(0, 0, image_data_cbc, 128, 64, 1);
  display.display();
  delay(2000);
  
  display.clearDisplay();
  initialise_lcd_layout_radio_channel_changing(radio_channel_value);
}

void initialise_lcd_layout_radio_channel_changing(uint8_t radio_channel_value_for_lcd){
  display.setTextColor(WHITE);
  display.setTextSize(1.5);
  display.setCursor(0, 10);
  display.println("CHANNEL SELECTOR");
  display.setCursor(0,30);
  display.setTextSize(2);
  display.println("CHANNEL");
  display.setCursor(0,55);
  display.setTextSize(1);
  display.println("WIRELESS ACTIVATED");
  display.drawRoundRect(95, 25, 33, 25, 2, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(100,30);
  display.setTextSize(2);
  display.println(radio_channel_value_for_lcd); 
  display.display();
}

void refresh_lcd_radio_channel_value_unlock(uint8_t radio_channel_value_for_lcd){
  display.fillRoundRect(95, 25, 33, 25, 2, WHITE);
  display.setTextColor(BLACK);
  display.setCursor(100,30);
  display.setTextSize(2);
  display.println(radio_channel_value_for_lcd);  
  display.display();
}

void refresh_lcd_radio_channel_value_lock(uint8_t radio_channel_value_for_lcd){
  display.fillRoundRect(95, 25, 33, 25, 2, BLACK);
  display.setTextColor(WHITE);
  display.setCursor(100,30);
  display.setTextSize(2);
  display.println(radio_channel_value_for_lcd); 
  display.display();  
}

void rotate(){ 
  if(lock_channel_LCD){ 
  detachInterrupt(digitalPinToInterrupt(RotaryCLK));
  static long rotary_previous_push = millis();
  long _rotary_current_push = millis();
  CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  && digitalRead(RotaryCLK) == 1
  if (CLKNow != CLKPrevious  && (_rotary_current_push - rotary_previous_push) >= DELAY_REBOND_TIME_ROTARY){
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) {
      if(radio_channel_value < 99) //we do not go above 100
        radio_channel_value++; 
      else
        radio_channel_value = 0; 
    } 
    else 
    {
      if(radio_channel_value < 1) //we do not go below 0
        radio_channel_value = 99;
      else
      // Encoder is rotating B direction so decrease
        radio_channel_value--;        
    }    
    rotary_previous_push = _rotary_current_push;
    CLKPrevious = CLKNow;  // Store last CLK state
  }
  attachInterrupt(digitalPinToInterrupt(RotaryCLK), rotate, CHANGE);
  }
}

// void pushButton(){
//   detachInterrupt(digitalPinToInterrupt(ButtonPushPin));
//   currentState==digitalRead(ButtonPushPin);
//   if(lastState == HIGH && currentState == LOW) {        // button is pressed
//     pressedTime = millis();
//     isPressing = true;
//     isLongDetected = false;
//   } else if(lastState == LOW && currentState == HIGH) { // button is released
//     isPressing = false;
//     releasedTime = millis();

//     long pressDuration = releasedTime - pressedTime;

//     if( pressDuration < SHORT_PRESS_TIME )
//       lock_channel_LCD = !lock_channel_LCD;
//   }

//   if(isPressing == true && isLongDetected == false) {
//     long pressDuration = millis() - pressedTime;

//     if( pressDuration > LONG_PRESS_TIME ) {
//       radio_activated = !radio_activated;
//       isLongDetected = true;
//       if(radio_activated){
//         display.fillRoundRect(0, 50, 33, 25, 2, BLACK);
//         display.setCursor(0,55);
//         display.setTextSize(1);
//         display.println("WIRELESS ACTIVATED");
//         display.display();
//       }
//       else{
//         display.fillRoundRect(0, 50, 100, 10, 2, BLACK);
//         display.setCursor(0,55);
//         display.setTextSize(1);
//         display.println("WIRELESS ACTIVATED");
//         display.display();
//       }
//     }
//   }

//   // save the the last state
//   lastState = currentState;

//   attachInterrupt(digitalPinToInterrupt(ButtonPushPin), pushButton, INPUT_PULLUP);
// }

// use this function to return the new radio channel values
void pushButton(){
  //anti rebond code
  static long previous_push = millis();
  long _current_push = millis();
  if ((_current_push - previous_push) >= DELAY_REBOND_TIME_BUTTON){
    detachInterrupt(digitalPinToInterrupt(ButtonPushPin));
    lock_channel_LCD = !lock_channel_LCD;

    attachInterrupt(digitalPinToInterrupt(ButtonPushPin), pushButton, INPUT_PULLUP);
  }

  previous_push = _current_push;
  
}
