#include "timer.h"
#include "utils.h"

int main()
{
        led_init();
        timer0_init();

        while (1) {
                timer0_exec();
        }

        return 0;
}