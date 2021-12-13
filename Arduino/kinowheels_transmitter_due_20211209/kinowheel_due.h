// getting back the values from the kinowheels for the sbus transmission and the software

#ifndef KINOWHEEL_DUE
#define KINOWHEEL_DUE

void kinowheel_begin();
uint16_t kinowheel_X_value();
uint16_t kinowheel_Y_value();
uint16_t kinowheel_Z_value();
// the software is using only the pulses from the rotative encoder
float kinowheel_pulsesX();
float kinowheel_pulsesY();

//pan
void XA_RISE();
void XA_FALL();
void XB_RISE();
void XB_FALL();
//tilt
void YA_RISE();
void YA_FALL();
void YB_RISE();
void YB_FALL();
//roll
void ZA_RISE();
void ZA_FALL();
void ZB_RISE();
void ZB_FALL();

#endif
