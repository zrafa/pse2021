/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"

int main(void)
{
	led_init();

	int delay = 400;
	int on = 0;
	int off = -1;

	while (1)
	{
		led_toggle(on, off); // Prende el led "on" y apaga el "off"
		delay_ms(delay);	 // Espera "delay" milisegundos

		if (on == 4)
		{
			on = 0; // Prende el último led, reinicia
		}
		else
		{
			on++; // Aumenta el led que se debe prender
		}

		if (off == -1)
		{
			off = 0; // Se debe apagar el primer led
		}
		else if (off == 4)
		{
			off = 0; // Apaga el último led, reinicia
		}
		else
		{
			off++; // Aumenta el led que se debe apagar
		}
	}

	return 0;
}
