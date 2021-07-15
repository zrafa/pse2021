#include "serial.h"
#include "timer.h"
#include "utils.h"
#include <avr/interrupt.h>

extern unsigned int ticks;
extern unsigned int toggle;
extern unsigned int seconds;

int main()
{
        serial_init();
        led_init();
        timer0_init();

        while (1) {
                char time[] = { '0', '0', '0', '0', '\n' };

                if (ticks == 0 && toggle) {
                        int_to_string(seconds, time);
                        print(time, 5);
                        led_toggle();

                        cli();
                        toggle = 0;
                        sei();
                }
        }

        return 0;
}