#include <stdint.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

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

void serial_init()
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
}

void serial_put_char(char c)
{
        // Mientras el bit 5 de status_control_a es 0 espera
        while (!(puerto_serial->status_control_a & (1 << 5))) { }

        // Escribe el dato en el registro de entrada/salida
        puerto_serial->data_es = c;
}

char serial_get_char()
{
        // Mientras el bit 7 de status_control_a es 0 espera
        while (!(puerto_serial->status_control_a & (1 << 7))) { }

        return puerto_serial->data_es;
}