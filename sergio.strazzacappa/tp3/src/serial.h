/**********************************************************************
 *
 * Filename:    serial.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _SERIAL_H
#define _SERIAL_H

void serial_init(void);
void serial_put_char(char c);
char serial_get_char(void);

void delay_ms(int milliseconds);

void blink_led(void);
void blinking_led_init(void);
void blinking_led_toggle(void);

void knight_rider(void);
void knight_rider_init(void);
void knight_rider_toggle(void);

#endif
