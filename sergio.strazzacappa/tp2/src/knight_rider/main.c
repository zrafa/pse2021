/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"

/*
 * Cantidad de milisegundos entre el prendido y el apagado de
 * un led.
 */
const int delay = 500;

/*
 * up = 1 si los leds se van encendiendo en orden ascendente, 
 * up = 0 si los leds se van encendiendo en orden descendiente.
 */
char up = 1;

/*
 * on es el led que se va a encender.
 * off es el led que se va a apagar, comienza en -1
 * ya que al principio todos los leds están apagados y
 * no es necesario apagar alguno.
 */
int on = 0;
int off = -1;

/*
 * off_status = 1 cuando cambia el sentido de encendidos 
 * (ascendente a descendente o viceversa) para que se apague el último led.
 * En caso contrario es 0.
 */

char off_status = 0;

int main(void)
{
	led_init();

	while (1)
	{
		led_toggle(on, off); // Prende el led "on" y apaga el "off"
		delay_ms(delay);	 // Espera "delay" milisegundos

		// Llegó al primer led en orden descendente
		if (on == 0 && !up)
		{
			up = 1; // Cambia el orden
			off--;	// Apaga el primer led
			off_status = 1;
		}
		else if (on == 4) // Llegó al último led en orden ascendente
		{
			up = 0; // Cambia el orden
			off++;	// Apaga el último led
			off_status = 1;
		}

		if (up) // Ascenso
		{
			on++; // Aumenta el led que se debe prender

			if (off == -1)
			{
				off = 0; // Se debe apagar el primer led
			}
			else if (!off_status)
			{
				off++; // Aumenta el led que se debe apagar
			}
		}
		else // Descenso
		{
			on--; // Decrementa el led que debe prender

			if (!off_status)
			{
				off--;
			}
		}
		off_status = 0;
	}

	return 0;
}
