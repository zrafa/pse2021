
#ifndef _CLOCK_H
#define _CLOCK_H

void timer0_init(void);
void set_time(void);
void set_decima(void);
void set_segundo(void);
void set_minuto(void);
void set_hora(void);
void int_to_string(int val, char number[], int length);
void mostrar_hora(void);

#endif
