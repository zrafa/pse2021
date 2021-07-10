#include "serial.h"
#include "timer.h"

int main()
{
        serial_init();
        timer0_init();
        fecha_init();

        extern unsigned int interrupted;

        while (1) {
                //print_number(interrupted, 1);
                print("", 0);
                if (interrupted) {
                        mostrar_fecha();
                        interrupted = 0;
                }
        }

        return 0;
}