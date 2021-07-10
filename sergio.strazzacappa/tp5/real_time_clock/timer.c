#include "timer.h"
#include "serial.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#define TIMER0_CTC (0x02) /* 0010 */
#define TIMER0_CS (0x03) /* 0011 - prescalar 64 */
#define SYSTEM_TICKS (16000000)
#define PRESCALAR (64)
#define TICKS_PER_SECOND (1000)
#define TIMER0_OCR0A (SYSTEM_TICKS / PRESCALAR / TICKS_PER_SECOND)
#define ANIO_BISIESTO (fecha_actual.anio % 4 == 0 || (fecha_actual.anio % 100 == 0 && fecha_actual.anio % 400 == 0))

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

struct fecha {
        unsigned int decima;
        unsigned int segundo;
        unsigned int minuto;
        unsigned int hora;
        unsigned int dia;
        unsigned int mes;
        unsigned int anio;
} fecha_actual;

unsigned int ticks;
unsigned int interrupted;

void timer0_init()
{
        interrupted = 1;
        ticks = 0;
        sei();
        timer0->tccr0a |= TIMER0_CTC; /* setea el modo a CTC */
        timer0->tccr0b |= TIMER0_CS; /* setea el prescalar a 64 */
        timer0->ocr0a = TIMER0_OCR0A; /* valor con el cual comprarar */
        (*timer0_timsk0) |= 0x02; /* habilita las interrupciones al comparar con el registro ocr0a */
}

void set_mes()
{
        if (fecha_actual.mes == 13) {
                fecha_actual.mes = 1;
                fecha_actual.anio++;
        }
}

void set_dia()
{
        if (fecha_actual.dia == 32) {
                fecha_actual.dia = 1;
                fecha_actual.mes++;
                set_mes();
        } else if (fecha_actual.dia == 31 && (fecha_actual.mes == 4 || fecha_actual.mes == 6 || fecha_actual.mes == 9 || fecha_actual.mes == 11)) {
                fecha_actual.dia = 1;
                fecha_actual.mes++;
                set_mes();
        } else if (fecha_actual.mes == 2 && fecha_actual.dia == 29 && !ANIO_BISIESTO) {
                fecha_actual.dia = 1;
                fecha_actual.mes++;
                set_mes();
        } else if (fecha_actual.mes == 2 && fecha_actual.dia == 30) {
                fecha_actual.dia = 1;
                fecha_actual.mes++;
                set_mes();
        }
}

void set_hora()
{
        if (fecha_actual.hora == 24) {
                fecha_actual.hora = 0;
                fecha_actual.dia++;
                set_dia();
        }
}

void set_minuto()
{
        if (fecha_actual.minuto == 60) {
                fecha_actual.minuto = 0;
                fecha_actual.hora++;
                set_hora();
        }
}

void set_segundo()
{
        if (fecha_actual.segundo == 60) {
                fecha_actual.segundo = 0;
                fecha_actual.minuto++;
                set_minuto();
        }
}

void set_decima()
{
        if (fecha_actual.decima == 10) {
                fecha_actual.decima = 0;
                fecha_actual.segundo++;
                set_segundo();
        }
}

void set_time()
{
        fecha_actual.decima++;
        set_decima();
}

void int_to_string(int val, char number[], int length)
{
        while (val > 0) {
                int digit = val % 10;
                val /= 10;
                number[length - 1] = 48 + digit;
                length--;
        }
}

void mostrar_fecha()
{
        char anio[] = { '0', '0', '0', '0' };
        char mes[] = { '0', '0' };
        char dia[] = { '0', '0' };
        char hora[] = { '0', '0' };
        char minuto[] = { '0', '0' };
        char segundo[] = { '0', '0' };
        char decima[] = { '0' };

        int_to_string(fecha_actual.anio, anio, 4);
        int_to_string(fecha_actual.mes, mes, 2);
        int_to_string(fecha_actual.dia, dia, 2);
        int_to_string(fecha_actual.hora, hora, 2);
        int_to_string(fecha_actual.minuto, minuto, 2);
        int_to_string(fecha_actual.segundo, segundo, 2);
        int_to_string(fecha_actual.decima, decima, 1);

        print(anio, 4);
        print("/", 1);
        print(mes, 2);
        print("/", 1);
        print(dia, 2);
        print(" - ", 3);
        print(hora, 2);
        print(":", 1);
        print(minuto, 2);
        print(":", 1);
        print(segundo, 2);
        print(".", 1);
        print(decima, 1);
        print("\n", 1);
}

ISR(TIMER0_COMPA_vect)
{
        ticks++;

        if (ticks == 100) { /* Pasó una decima de segundo */
                interrupted = 1;
                ticks = 0;
                set_time();
        }
}

void fecha_init()
{
        fecha_actual.decima = 0;
        fecha_actual.segundo = 0;
        fecha_actual.minuto = 0;
        fecha_actual.hora = 0;
        fecha_actual.dia = 0;
        fecha_actual.mes = 0;
        fecha_actual.anio = 0;
}

unsigned int get_decima()
{
        return fecha_actual.decima;
}