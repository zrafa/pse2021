/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"

int main(void)
{
        serial_init();

        serial_put_char('s');
        serial_put_char('t');
        serial_put_char('a');
        serial_put_char('r');
        serial_put_char('t');
        serial_put_char('\r');
        serial_put_char('\n');

        char rcvChar = 0;

        while (rcvChar != 'q') {
                if (rcvChar == 'c') {
                        // Blink_led hace 5 parpadeos
                        blink_led();

                } else if (rcvChar == 'k') {
                        // Knight_rider da una vuelta
                        knight_rider();
                }

                rcvChar = serial_get_char();

                serial_put_char(rcvChar);
                serial_put_char('\r');
                serial_put_char('\n');
        }

        for (;;) { }

        return 0;
}
