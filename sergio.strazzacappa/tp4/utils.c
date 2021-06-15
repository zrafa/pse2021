#define CYCLES_PER_MS (200);

int led_bits[] = {
        0x01,
        0x02,
        0x08,
        0x10,
        0x20
};

volatile unsigned char* DDR_B = (unsigned char*)0x24;
volatile unsigned char* PORT_B = (unsigned char*)0x25;

void led_init()
{
        for (int i = 0; i < 5; i++) {
                *DDR_B = *DDR_B | led_bits[i];
                *PORT_B = *PORT_B & ~led_bits[i];
        }
}

void led_toggle(int on, int off)
{
        unsigned char status;

        status = *PORT_B;
        status = status ^ led_bits[on];

        if (off != -1) {
                status = status ^ led_bits[off];
        }

        *PORT_B = status;
}

void delay_ms(int milliseconds)
{
        volatile long long cycles = (long long)milliseconds * CYCLES_PER_MS;

        while (cycles != 0) {
                cycles--;
        }
}