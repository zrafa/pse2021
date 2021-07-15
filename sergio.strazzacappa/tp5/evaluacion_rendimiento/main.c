#include "serial.h"
#include "timer.h"

int main()
{
        unsigned int cant_serial = 0;
        serial_init();
        timer0_init();
        fecha_set(0, 0, 0, 0, 0, 0);

        while (get_segundo() == 0) {
                serial_put_char('A');
                cant_serial++;
        }

        unsigned int cant_digits = 0;
        unsigned int temp = cant_serial;

        while (temp > 0) {
                temp /= 10;
                cant_digits++;
        }

        print("\n", 1);
        print("La cantidad de caracteres transmitidos es de: ", 46);
        print_number(cant_serial, cant_digits);
        print("\n", 1);

        for (;;) { }

        return 0;
}