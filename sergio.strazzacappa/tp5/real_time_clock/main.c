#include "serial.h"
#include "timer.h"
#include <avr/interrupt.h>

int main()
{
        serial_init();
        timer0_init();
        fecha_init();

        extern unsigned int interrupted;

        while (1) {
                print("", 0);
                if (interrupted) {
                        mostrar_fecha();

                        cli();
                        interrupted = 0;
                        sei();
                }
        }

        return 0;
}