#ifndef _SERIAL_H
#define _SERIAL_H

void serial_init();
void serial_put_char(char c);
char serial_get_char();
void print(char string[], int len);
void print_number(int number, int digits);
#endif
