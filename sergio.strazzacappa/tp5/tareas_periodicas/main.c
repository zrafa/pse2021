#include <avr/interrupt.h>
#include <stdio.h>

#include "serial.h"
#include "tasks.h"
#include "timer.h"
#include "utils.h"

int main(void)
{
        timer0_init();
        leds_init();
        tasks_init();
        serial_init();

        /* definimos las tareas periodicas */
        tasks_def(300, toggle13);
        tasks_def(500, led_toggle);
        tasks_def(1000, hello_world);
        tasks_def(1500, mostrar_hora);

        /* habilitamos las interrupciones */
        sei();

        while (1) {
                tasks_do();
        }

        return 0;
}
