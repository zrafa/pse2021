#ifndef _UTILS_H
#define _UTILS_H

void delay_ms(int milliseconds);

void blink_led_init();
void blink_led_toggle();
void blink_led();

void knight_rider_init();
void knight_rider_toggle(int on, int off);
void knight_rider();

#endif