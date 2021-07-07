/*
 * PB5 = 13
 * PB4 = 12
 * PB3 = 11
 * PB2 = 10
 * PB1 = 9
 * PB0 = 8
 */

#define CYCLES_PER_MS (200);
#define LED_BIT (0x02); /* 0000 0010 */

volatile unsigned char* DDR_B = (unsigned char*)0x24;
volatile unsigned char* PORT_B = (unsigned char*)0x25;

void led_init()
{
        *DDR_B |= LED_BIT;
        *PORT_B &= ~LED_BIT;
}

void led_toggle()
{
        unsigned char status = *PORT_B;
        status ^= LED_BIT;
        *PORT_B = status;
}

void delay_ms(int milliseconds)
{
        volatile long long cycles = (long long)milliseconds * CYCLES_PER_MS;

        while (cycles != 0) {
                cycles--;
        }
}