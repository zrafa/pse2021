#include <stdint.h>

typedef struct
{
        uint8_t adc_l;
        uint8_t adc_h;
        uint8_t adcsra;
        uint8_t adcsrb;
        uint8_t admux;
        uint8_t reserved;
        uint8_t didr0;

} volatile adc_t;

volatile adc_t* puerto_adc = (adc_t*)(0x78);

void adc_init()
{
        /*
         * Testear con diferentes voltajes de referencias. Bits 7 y 6.
         * 
         * Configuración:
         * Voltaje de referencia interno
         * Ajustado a derecha
         * Canal usado: ADC0
         * 
         * ADMUX = 1111 0000
         */
        puerto_adc->admux = 0xf0;

        /*
         * ADCSRA = 1000 0111
         */
        puerto_adc->adcsra = 0x87;
}

int adc_get(char input)
{
        int val;

        puerto_adc->admux |= input; // Cambió el canal de entrada a input
        puerto_adc->adcsra != (1 << 6); // Inicia conversión

        while (!(puerto_adc->adcsra & (1 << 6))) { }

        // Convierte el valor leído en los 2 registros a decimal
        val = puerto_adc->adc_l;

        if (puerto_adc->adc_h & 1) {
                val += 256;
        }

        if (puerto_adc->adc_h & (1 << 1)) {
                val += 512;
        }

        return val;
}