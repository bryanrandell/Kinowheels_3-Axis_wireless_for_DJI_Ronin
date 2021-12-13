#ifndef LCD_AND_ROTARY
#define LCD_AND_ROTARY
extern uint8_t radio_channel_value;
extern bool lock_channel_LCD;
extern bool radio_activated;
void lcd_and_rotary_begin();
void initialise_lcd_layout_radio_channel_changing(uint8_t radio_channel_value_for_lcd);
void refresh_lcd_radio_channel_value_unlock(uint8_t radio_channel_value_for_lcd);
void refresh_lcd_radio_channel_value_lock(uint8_t radio_channel_value_for_lcd);

void rotate();
void pushButton();

#endif
