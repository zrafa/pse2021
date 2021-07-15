#ifndef _TIMER_
#define _TIMER_

void set_mes();
void set_dia();
void set_hora();
void set_minuto();
void set_segundo();
void set_decima();
void set_time();
void int_to_string(int val, char number[], int length);
void timer0_init();
void fecha_set(
    unsigned int anio, unsigned int mes, unsigned int dia,
    unsigned int hora, unsigned int minuto, unsigned int segundo);
unsigned int get_segundo();

#endif