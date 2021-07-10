#ifndef _TIMER_
#define _TIMER_

extern unsigned int ticks;
extern unsigned int toggle;
extern unsigned int seconds;

void timer0_init();
void int_to_string(int val, char number[]);

#endif