#include <Arduino.h>
#include "kinowheel_due.h"

// PINS
//roll analog 3
const uint8_t potAmpliPinX = 1, potAmpliPinY = 2, potAmpliPinZ = 3, inverter_switch_x_pin=6, inverter_switch_y_pin=5, inverter_switch_z_pin=4;

// -------- Les trois coefficiants à modifier pour la multiplication du mouvement wheel -----------
const uint8_t coefficiantPAN = 150;
const uint8_t coefficiantTILT = 150;
const uint8_t coefficiantROLL = 150;
// -------- Les trois coefficiants à modifier pour la multiplication du mouvement wheel -----------

const uint16_t sbus_zero_val = 1023, sbus_min_value = 172, sbus_max_value = 1811;

// kinowheels variables
bool inverter_switch_x, inverter_switch_y, inverter_switch_z;
uint8_t XA_SIG=0, XB_SIG=1, YA_SIG=0, YB_SIG=1, ZA_SIG=0, ZB_SIG=1;
//long for the software using the wheels
float float_pulsesX;
float float_pulsesY;
int16_t pulsesX;
int16_t pulsesY; 
int16_t pulsesZ;
int16_t deltaPulsesX, deltaPulsesY, deltaPulsesZ, oldPulsesX, oldPulsesY, oldPulsesZ;


void kinowheel_begin(){
  // inverter pin setup
  pinMode(inverter_switch_x_pin,INPUT);
  pinMode(inverter_switch_y_pin,INPUT);
  pinMode(inverter_switch_z_pin,INPUT); //4)
  
  // pan interrupt
  attachInterrupt(digitalPinToInterrupt(2), XA_RISE, RISING); // Pin 2 (base 0)
  attachInterrupt(digitalPinToInterrupt(3), XB_RISE, RISING); // Pin 3 (base 1)
  //tilt interrupt
  attachInterrupt(digitalPinToInterrupt(19), YA_RISE, RISING); // Pin 19 (base 4) passe en 6
  attachInterrupt(digitalPinToInterrupt(18), YB_RISE, RISING); // Pin 18 (base 5) passe en 7
  // roll interrupt
  attachInterrupt(digitalPinToInterrupt(22), ZA_RISE, RISING); // Pin 18 (base 5) passe en 7
  attachInterrupt(digitalPinToInterrupt(23), ZB_RISE, RISING); // Pin 18 (base 5) passe en 7

}


uint16_t kinowheel_X_value(){
    uint16_t multiplicatorX = constrain(analogRead(potAmpliPinX), 0, 1000) / coefficiantPAN;      
    deltaPulsesX = (pulsesX - oldPulsesX) * multiplicatorX;   
    uint16_t X_value = constrain(sbus_zero_val + deltaPulsesX, sbus_min_value, sbus_max_value);
    // renew variables values
    oldPulsesX = pulsesX;
    return X_value;
}

uint16_t kinowheel_Y_value(){
    uint16_t multiplicatorY = constrain(analogRead(potAmpliPinY), 0, 1000) / coefficiantTILT;
    deltaPulsesY = (pulsesY - oldPulsesY) * multiplicatorY;
    uint16_t Y_value = constrain(sbus_zero_val + deltaPulsesY, sbus_min_value, sbus_max_value);
    // renew variables values
    oldPulsesY = pulsesY;
    return Y_value;
}

uint16_t kinowheel_Z_value(){
    uint16_t multiplicatorZ = constrain(analogRead(potAmpliPinZ), 0, 1000) / coefficiantROLL;
    deltaPulsesZ = (pulsesZ - oldPulsesZ) * multiplicatorZ;
    uint16_t Z_value = constrain(sbus_zero_val + deltaPulsesZ, sbus_min_value, sbus_max_value);
    // renew variables values
    oldPulsesZ = pulsesZ;
    return Z_value;
}
// the software is using only the pulses from the rotative encoder

float kinowheel_pulsesX(){
  return float_pulsesX;
}
float kinowheel_pulsesY(){
  return float_pulsesY;
}


//X-Axis
// using float_pulsesX += (1 * (analogRead(potAmpliPinX) / 512.0)) for the ampli potar

void XA_RISE(){
 detachInterrupt(digitalPinToInterrupt(2));
 //delay(1);
 XA_SIG=1;
 inverter_switch_x = digitalRead(inverter_switch_x_pin);
 
 if(XB_SIG==0 && inverter_switch_x==0){
   pulsesX++; 
   float_pulsesX++;}
 if(XB_SIG==1 && inverter_switch_x==0){
   pulsesX--; 
   float_pulsesX--;}
 if(XB_SIG==0 && inverter_switch_x==1){
   pulsesX--; 
   float_pulsesX--;}
 if(XB_SIG==1 && inverter_switch_x==1){
   pulsesX++; 
   float_pulsesX++;}
 

 attachInterrupt(digitalPinToInterrupt(2), XA_FALL, FALLING);
}

void XA_FALL(){
  detachInterrupt(digitalPinToInterrupt(2));
  //delay(1);
 XA_SIG=0;
 inverter_switch_x = digitalRead(inverter_switch_x_pin);
 
 if(XB_SIG==1 && inverter_switch_x==0){
   pulsesX++; 
   float_pulsesX++;}
 if(XB_SIG==0 && inverter_switch_x==0){
   pulsesX--; 
   float_pulsesX--;}
 if(XB_SIG==1 && inverter_switch_x==1){
   pulsesX--; 
   float_pulsesX--;}
 if(XB_SIG==0 && inverter_switch_x==1){
   pulsesX++; 
   float_pulsesX++;}

 attachInterrupt(digitalPinToInterrupt(2), XA_RISE, RISING);  
}

void XB_RISE(){
 detachInterrupt(digitalPinToInterrupt(3));
 //delay(1);
 XB_SIG=1;
 inverter_switch_x = digitalRead(inverter_switch_x_pin);
 
 if(XA_SIG==1 && inverter_switch_x==0){
   pulsesX++; 
   float_pulsesX++;}
 if(XA_SIG==0 && inverter_switch_x==0){
   pulsesX--; 
   float_pulsesX--;}
 if(XA_SIG==1 && inverter_switch_x==1){
   pulsesX--; 
   float_pulsesX--;}
 if(XA_SIG==0 && inverter_switch_x==1){
   pulsesX++; 
   float_pulsesX++;}

 attachInterrupt(digitalPinToInterrupt(3), XB_FALL, FALLING);
}

void XB_FALL(){
 detachInterrupt(digitalPinToInterrupt(3));
 //delay(1);
 XB_SIG=0;
 inverter_switch_x = digitalRead(inverter_switch_x_pin);
 
 if(XA_SIG==0 && inverter_switch_x==0){
   pulsesX++; 
   float_pulsesX++;}
 if(XA_SIG==1 && inverter_switch_x==0){
   pulsesX--; 
   float_pulsesX--;}
 if(XA_SIG==0 && inverter_switch_x==1){
   pulsesX--; 
   float_pulsesX--;}
 if(XA_SIG==1 && inverter_switch_x==1){
   pulsesX++; 
   float_pulsesX++;}

 attachInterrupt(digitalPinToInterrupt(3), XB_RISE, RISING);
}

//Y-Axis

void YA_RISE(){
 detachInterrupt(digitalPinToInterrupt(19));
 //delay(1);
 YA_SIG=1;
 inverter_switch_y = digitalRead(inverter_switch_y_pin);
 
 if(YB_SIG==0 && inverter_switch_y==0){
   pulsesY++; 
   float_pulsesY++;}
 if(YB_SIG==1 && inverter_switch_y==0){
   pulsesY--; 
   float_pulsesY--;}
 if(YB_SIG==0 && inverter_switch_y==1){
   pulsesY--; 
   float_pulsesY--;}
 if(YB_SIG==1 && inverter_switch_y==1){
   pulsesY++; 
   float_pulsesY++;}

 attachInterrupt(digitalPinToInterrupt(19), YA_FALL, FALLING);
}

void YA_FALL(){
  detachInterrupt(digitalPinToInterrupt(19));
  //delay(1);
 YA_SIG=0;
 inverter_switch_y = digitalRead(inverter_switch_y_pin);
 
 if(YB_SIG==1 && inverter_switch_y==0 ){
   pulsesY++; 
   float_pulsesY++;}
 if(YB_SIG==0 && inverter_switch_y==0 ){
   pulsesY--; 
   float_pulsesY--;}
 if(YB_SIG==1 && inverter_switch_y==1 ){
   pulsesY--; 
   float_pulsesY--;}
 if(YB_SIG==0 && inverter_switch_y==1 ){
   pulsesY++; 
   float_pulsesY++;}

 attachInterrupt(digitalPinToInterrupt(19), YA_RISE, RISING);  
}

void YB_RISE(){
 detachInterrupt(digitalPinToInterrupt(18));
 //delay(1);
 YB_SIG=1;
 inverter_switch_y = digitalRead(inverter_switch_y_pin);
 
 if(YA_SIG==1 && inverter_switch_y==0){
   pulsesY++; 
   float_pulsesY++;}
 if(YA_SIG==0 && inverter_switch_y==0){
   pulsesY--; 
   float_pulsesY--;}
 if(YA_SIG==1 && inverter_switch_y==1){
   pulsesY--; 
   float_pulsesY--;}
 if(YA_SIG==0 && inverter_switch_y==1){
   pulsesY++; 
   float_pulsesY++;}

 attachInterrupt(digitalPinToInterrupt(18), YB_FALL, FALLING);
}

void YB_FALL(){
 detachInterrupt(digitalPinToInterrupt(18));
 //delay(1);
 YB_SIG=0;
 inverter_switch_y = digitalRead(inverter_switch_y_pin);
 
 if(YA_SIG==0 && inverter_switch_y==0){
   pulsesY++; 
   float_pulsesY++;}
 if(YA_SIG==1 && inverter_switch_y==0){
   pulsesY--; 
   float_pulsesY--;}
 if(YA_SIG==0 && inverter_switch_y==1){
   pulsesY--; 
   float_pulsesY--;}
 if(YA_SIG==1 && inverter_switch_y==1){
   pulsesY++; 
   float_pulsesY++;}

 attachInterrupt(digitalPinToInterrupt(18), YB_RISE, RISING);
}

//Z-Axis

void ZA_RISE(){
 detachInterrupt(digitalPinToInterrupt(22));
 //delay(1);
 ZA_SIG=1;
 inverter_switch_z = digitalRead(inverter_switch_z_pin);
 
 if(ZB_SIG==0 && inverter_switch_z==0)
 pulsesZ++;//moving forward
 if(ZB_SIG==1 && inverter_switch_z==0)
 pulsesZ--;//moving reverse
 if(ZB_SIG==0 && inverter_switch_z==1)
 pulsesZ--;//moving forward
 if(ZB_SIG==1 && inverter_switch_z==1)
 pulsesZ++;//moving reverse

 attachInterrupt(digitalPinToInterrupt(22), ZA_FALL, FALLING);
}

void ZA_FALL(){
  detachInterrupt(digitalPinToInterrupt(22));
  //delay(1);
 ZA_SIG=0;
 inverter_switch_z = digitalRead(inverter_switch_z_pin);
 
 if(ZB_SIG==1 && inverter_switch_z==0 )
 pulsesZ++;//moving forward
 if(ZB_SIG==0 && inverter_switch_z==0 )
 pulsesZ--;//moving reverse
 if(ZB_SIG==1 && inverter_switch_z==1 )
 pulsesZ--;//moving forward
 if(ZB_SIG==0 && inverter_switch_z==1 )
 pulsesZ++;//moving reverse

 attachInterrupt(digitalPinToInterrupt(22), ZA_RISE, RISING);  
}

void ZB_RISE(){
 detachInterrupt(digitalPinToInterrupt(23));
 //delay(1);
 ZB_SIG=1;
 inverter_switch_z = digitalRead(inverter_switch_z_pin);
 
 if(ZA_SIG==1 && inverter_switch_z==0)
 pulsesZ++;//moving forward
 if(ZA_SIG==0 && inverter_switch_z==0)
 pulsesZ--;//moving reverse
 if(ZA_SIG==1 && inverter_switch_z==1)
 pulsesZ--;//moving forward
 if(ZA_SIG==0 && inverter_switch_z==1)
 pulsesZ++;//moving reverse

 attachInterrupt(digitalPinToInterrupt(23), ZB_FALL, FALLING);
}

void ZB_FALL(){
 detachInterrupt(digitalPinToInterrupt(23));
 //delay(1);
 ZB_SIG=0;
 inverter_switch_z = digitalRead(inverter_switch_z_pin);
 
 if(ZA_SIG==0 && inverter_switch_z==0)
 pulsesZ++;//moving forward
 if(ZA_SIG==1 && inverter_switch_z==0)
 pulsesZ--;//moving reverse
 if(ZA_SIG==0 && inverter_switch_z==1)
 pulsesZ--;//moving forward
 if(ZA_SIG==1 && inverter_switch_z==1)
 pulsesZ++;//moving reverse

 attachInterrupt(digitalPinToInterrupt(23), ZB_RISE, RISING);
}
