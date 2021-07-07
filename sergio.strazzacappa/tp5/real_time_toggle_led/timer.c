#include "utils.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#define TIMER0_CTC (0x02) /* 0010 */
#define TIMER0_CS (0x03) /* 0011 - prescalar 64 */
#define SYSTEM_TICKS (16000000)
#define PRESCALAR (64)
#define TICKS_PER_SECOND (1000)
#define TIMER0_OCR0A (SYSTEM_TICKS / PRESCALAR / TICKS_PER_SECOND)

unsigned int ticks = 0;
unsigned int toggle = 1;

ISR(TIMER0_COMPA_vect)
{
        ticks++;

        if (ticks == 1000) {
                ticks = 0;
                toggle = 1;
        }
}

typedef struct
{
        uint8_t tccr0a;
        uint8_t tccr0b;
        uint8_t tcnt0;
        uint8_t ocr0a;
        uint8_t ocr0b;
} volatile timer0_t;

volatile timer0_t* timer0 = (timer0_t*)(0x44);

volatile unsigned char* timer0_timsk0 = (unsigned char*)(0x6e);

void timer0_init()
{
        timer0->tccr0a |= TIMER0_CTC; /* setea el modo a CTC */
        timer0->tccr0b |= TIMER0_CS; /* setea el prescalar a 64 */
        timer0->ocr0a = TIMER0_OCR0A; /* valor con el cual comprarar */
        (*timer0_timsk0) |= 0x02; /* habilita las interrupciones al comparar con el registro ocr0a */
}

void timer0_exec()
{
        if (ticks == 0 && toggle) {
                led_toggle();
                toggle = 0;
        }
}