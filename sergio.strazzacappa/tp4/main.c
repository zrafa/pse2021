#include "adc.h"
#include "serial.h"

void int_to_string(int val, char number[])
{
        int i = 2;

        while (val > 0) {
                int digit = val % 10;
                val /= 10;
                number[i] = 48 + digit;
                i--;
        }
}

int main()
{
        int val;
        char number[3] = { '0', '0', '0' };

        serial_init();
        adc_init();

        val = adc_get(0);
        int_to_string(val, number);

        serial_put_char(number[0]);
        serial_put_char(number[1]);
        serial_put_char(number[2]);
        serial_put_char('\r');
        serial_put_char('\n');

        for (;;) { }

        return 0;
}