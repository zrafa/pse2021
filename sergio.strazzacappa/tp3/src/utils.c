#define LED_ROJO (0x20); // 0010 0000 (bit 5 de DDRB)
#define CYCLES_PER_MS (200);
#define DELAY (500)

int led_bits[] = {
        0x01, // Bit 0 - 0000 0001
        0x02, // Bit 1 - 0000 0010
        0x08, // Bit 3 - 0000 1000
        0x10, // bit 4 - 0001 0000
        0x20 // bit 5 - 0010 0000
};

volatile unsigned char* DDR_B = (unsigned char*)0x24;
volatile unsigned char* PORT_B = (unsigned char*)0x25;

void delay_ms(int milliseconds)
{
        volatile long long cycles = (long long)milliseconds * CYCLES_PER_MS;

        while (cycles != 0) {
                cycles--;
        }
}

/*
 ********************************************
 *************** BLINKING LED ***************
 ********************************************
 */

void blink_led_init()
{
        *PORT_B = *PORT_B & ~LED_ROJO; // Coloca 0 en el bit 5 de PORTB
        *DDR_B = *DDR_B | LED_ROJO; // Coloca 1 en el bit 5 de DDRB
}

void blink_led_toggle()
{
        unsigned char status;

        status = *PORT_B; // status almacena el estado actual del led
        status = status ^ LED_ROJO; // cambia el status
        *PORT_B = status; // vuelve a almacenar el status en el PORTB
}

void blink_led()
{
        blink_led_init();

        for (int i = 0; i < 10; i++) {
                blink_led_toggle();
                delay_ms(DELAY);
        }
}

/*
 ********************************************
 *************** KNIGHT RIDER ***************
 ********************************************
 */

void knight_rider_init()
{
        for (int i = 0; i < 5; i++) {
                *DDR_B = *DDR_B | led_bits[i]; // Setea el bit i de DDRB a 1 (output)
                *PORT_B = *PORT_B & ~led_bits[i]; // Setea el bit i de PORTB a 0 (apaga)
        }
}

void knight_rider_toggle(int on, int off)
{
        unsigned char status;

        status = *PORT_B;

        if (on != -1) {
                status = status ^ led_bits[on];
        }

        if (off != -1) {
                status = status ^ led_bits[off];
        }

        *PORT_B = status;
}

void knight_rider()
{
        char up = 1;
        int on = 0;
        int off = -1;
        char off_status = 0;

        knight_rider_init();

        for (int i = 0; i < 9; i++) {
                knight_rider_toggle(on, off);
                delay_ms(DELAY);

                if (on == 0 && !up) {
                        up = 1;
                        off--;
                        off_status = 1;
                } else if (on == 4) {
                        up = 0;
                        off++;
                        off_status = 1;
                }
                if (up) {
                        on++;
                        if (off == -1) {
                                off = 0;
                        } else if (!off_status) {
                                off++;
                        }
                } else {
                        on--;
                        if (!off_status) {
                                off--;
                        }
                }
                off_status = 0;
        }
        knight_rider_toggle(-1, off);
}