/**********************************************************************
 *
 * utils.c - Funciones de utilidad
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/
#include "utils.h"

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */
#define PB5 (0x20) /* 0b 0010 0000 PIN 13 en placa */

#define LED_BIT (0x02); /* 0000 0010 */

/* puertos de E/S */
volatile unsigned char* PORTB = (unsigned char*)0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char* DDRB = (unsigned char*)0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char* PINB = (unsigned char*)0x23; /* direccion PIN B (registro de datos)*/

/* funciones */

void toggle13()
{
        *PORTB ^= PB5;
}

void led_toggle()
{
        unsigned char status = *PORTB;
        status ^= LED_BIT;
        *PORTB = status;
}

void leds_init()
{
        /* setea en OFF el voltaje de los pines */
        *PORTB &= (~PB5);
        *PORTB &= ~LED_BIT;

        /* setea pines en modo OUTPUT */
        *DDRB |= (PB5);
        *DDRB |= LED_BIT;
}
