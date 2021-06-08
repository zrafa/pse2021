
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define LED_ROJO (0x20); // 0010 0000 (bit 5 de DDRB)
#define CYCLES_PER_MS (200);

typedef struct
{
        uint8_t status_control_a;
        uint8_t status_control_b;
        uint8_t status_control_c;
        uint8_t reserved;
        uint8_t baud_rate_l;
        uint8_t baud_rate_h;
        uint8_t data_es;

} volatile uart_t;

uart_t* puerto_serial = (uart_t*)(0xc0);

void serial_init(void)
{

        // Configurar el BAUD RATE
        puerto_serial->baud_rate_l = BAUD_PRESCALE;
        puerto_serial->baud_rate_h = BAUD_PRESCALE >> 8;

        /*
         * Configurar FRAME de 8 bits sin bit de PARIDAD y con bit de STOP
         *
         * Registro C
         * Bit 7 y 6 = Selección de modo (sincronico o asincronico)
         * Bit 5 y 4 = Modo de paridad
         * Bit 3 = Stop bit mode (1 bit o 2 bits de stop)
         * Bit 2 y 1 = Tamaño de frame (Junto al bit 2 del registro B)
         * Bit 0 = Polaridad del reloj
         * 
         * Registro C = 0000 0110
         */
        puerto_serial->status_control_c = 0x06;

        /*
         * Registro B
         * Bit 7 = Habilita interrupciones del receptor
         * Bit 6 = Habilita interrupcionesl del emisor
         * Bit 4 = Habilita al receptor
         * Bit 3 = Habilita al emisor
         * Bit 2 = Tamaño de frame
         * Registro B = 0001 1000
         */
        puerto_serial->status_control_b = 0x18;

        volatile unsigned char* DDR_B = (unsigned char*)0x24;
        volatile unsigned char* PORT_B = (unsigned char*)0x25;

        *PORT_B = *PORT_B & ~LED_ROJO; // Coloca 0 en el bit 5 de PORTB
        *DDR_B = *DDR_B | LED_ROJO; // Coloca 1 en el bit 5 de DDRB
}

void serial_put_char(char c)
{
        // Mientras el bit 5 de status_control_a es 0 espera
        while (!(puerto_serial->status_control_a & (1 << 5))) { }

        // Escribe el dato en el registro de entrada/salida
        puerto_serial->data_es = c;
}

char serial_get_char(void)
{
        // Mientras el bit 7 de status_control_a es 0 espera
        while (!(puerto_serial->status_control_a & (1 << 7))) { }

        return puerto_serial->data_es;
}

void delay_ms(int milliseconds)
{
        volatile long long cycles = (long long)milliseconds * CYCLES_PER_MS;

        while (cycles != 0) {
                cycles--;
        }
}

void blinking_led_init(void)
{
        volatile unsigned char* DDR_B = (unsigned char*)0x24;
        volatile unsigned char* PORT_B = (unsigned char*)0x25;

        *PORT_B = *PORT_B & ~LED_ROJO; // Coloca 0 en el bit 5 de PORTB
        *DDR_B = *DDR_B | LED_ROJO; // Coloca 1 en el bit 5 de DDRB
}

void blinking_led_toggle(void)
{
        volatile unsigned char* PORT_B = (unsigned char*)0x25;
        unsigned char status;

        status = *PORT_B; // status almacena el estado actual del led
        status = status ^ LED_ROJO; // cambia el status
        *PORT_B = status; // vuelve a almacenar el status en el PORTB
}

void blink_led(void)
{
        const int delay = 500;
        blinking_led_init();

        for (int i = 0; i < 10; i++) {
                blinking_led_toggle();
                delay_ms(delay);
        }
}

void knight_rider_init(void)
{
        int led_bits[] = {
                0x01, // Bit 0 - 0000 0001
                0x02, // Bit 1 - 0000 0010
                0x08, // Bit 3 - 0000 1000
                0x10, // bit 4 - 0001 0000
                0x20 // bit 5 - 0010 0000
        };

        volatile unsigned char* DDR_B = (unsigned char*)0x24;
        volatile unsigned char* PORT_B = (unsigned char*)0x25;

        for (int i = 0; i < 5; i++) {
                *DDR_B = *DDR_B | led_bits[i]; // Setea el bit i de DDRB a 1 (output)
                *PORT_B = *PORT_B & ~led_bits[i]; // Setea el bit i de PORTB a 0 (apaga)
        }
}

void knight_rider_toggle(int on, int off)
{
        int led_bits[] = {
                0x01, // Bit 0 - 0000 0001
                0x02, // Bit 1 - 0000 0010
                0x08, // Bit 3 - 0000 1000
                0x10, // bit 4 - 0001 0000
                0x20 // bit 5 - 0010 0000
        };

        volatile unsigned char* PORT_B = (unsigned char*)0x25;
        unsigned char status;

        status = *PORT_B;

        if (on != -1) {
                status = status ^ led_bits[on];
        }

        if (off != -1) {
                status = status ^ led_bits[off];
        }

        *PORT_B = status;

        return;
}

void knight_rider()
{
        const int delay = 500;
        char up = 1;
        int on = 0;
        int off = -1;
        char off_status = 0;

        knight_rider_init();

        for (int i = 0; i < 9; i++) {
                knight_rider_toggle(on, off);
                delay_ms(delay);

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