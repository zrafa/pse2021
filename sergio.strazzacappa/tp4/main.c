#include "adc.h"
#include "serial.h"
#include "utils.h"

void int_to_string(int val, char number[])
{
        int i = 3;

        while (val > 0) {
                int digit = val % 10;
                val /= 10;
                number[i] = 48 + digit;
                i--;
        }
}

void to_scale(int val, char scale[])
{
        if (val >= 0 && val < 128) {
                scale[0] = '0';
        } else if (val >= 128 && val < 256) {
                scale[0] = '1';
        } else if (val >= 256 && val < 384) {
                scale[0] = '2';
        } else if (val >= 384 && val < 512) {
                scale[0] = '3';
        } else if (val >= 512 && val < 640) {
                scale[0] = '4';
        } else if (val >= 640 && val < 768) {
                scale[0] = '5';
        } else if (val >= 768 && val < 896) {
                scale[0] = '6';
        } else {
                scale[0] = '7';
        }
}

void print(char string[], int len)
{
        for (int i = 0; i < len; i++) {
                serial_put_char(string[i]);
        }
}

void toggle_leds(char number[], char scale[])
{
        print("VALOR = ", 8);
        print(number, 4);
        print(" - ", 3);
        print("ESCALA = ", 9);
        print(scale, 1);
        print("\r\n", 2);

        switch (scale[0]) {
        case '0':
                led_toggle(-1, 0);
                led_toggle(-1, 1);
                led_toggle(-1, 2);
                break;
        case '1':
                led_toggle(-1, 0);
                led_toggle(-1, 1);
                led_toggle(2, -1);
                break;
        case '2':
                led_toggle(-1, 0);
                led_toggle(1, -1);
                led_toggle(-1, 2);
                break;
        case '3':
                led_toggle(-1, 0);
                led_toggle(1, -1);
                led_toggle(2, -1);
                break;
        case '4':
                led_toggle(0, -1);
                led_toggle(-1, 1);
                led_toggle(-1, 2);
                break;
        case '5':
                led_toggle(0, -1);
                led_toggle(-1, 1);
                led_toggle(2, -1);
                break;
        case '6':
                led_toggle(0, -1);
                led_toggle(1, -1);
                led_toggle(-1, 2);
                break;
        case '7':
                led_toggle(0, -1);
                led_toggle(1, -1);
                led_toggle(2, -1);
                break;

        default:
                print("ERROR LEDS", 10);
                break;
        }
}

int main()
{
        int val;

        led_init();
        serial_init();
        adc_init();

        while (1) {
                char number[] = { '0', '0', '0', '0' };
                char scale[] = { '0' };

                val = adc_get(0);
                int_to_string(val, number);
                to_scale(val, scale);
                toggle_leds(number, scale);
                delay_ms(1000);
        }

        for (;;) { }

        return 0;
}