# Kinowheels_for_Ronin_wireless

# Description
Use the kinowheels from https://www.kinowheels.com/ to command a DJI Ronin via SBUS protocol using Arduino boards.

# Main Hardware
1x Arduino DUE (transmitter). 
1x Arduino NANO (receiver). 
2x Nrf24L01 (wireless 2,4 GHz module). 
2x LCD 0.96' Adafruit I2C (using Adafruit SSD1306 library). 
2x Rotary encoder SPI (for interaction with the lcd fonction, for now only modify nrf24 channel). 
3x Potentiometer (used to amplify or reduce the kinowheel values send to the SBUS). 
3x Toggle Switch (to invert the wheel rotation). 
2x SN74HC logical inverter (required for transmitting SBUS signal). 

Still work in progress, will upload tutos and photos
