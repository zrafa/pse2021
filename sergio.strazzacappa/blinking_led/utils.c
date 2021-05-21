/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#define LED_ROJO (0x20); // 0010 0000 (bit 5 de DDRB)
#define CYCLES_PER_MS (450);

volatile unsigned char *pin_b = (unsigned char *)0x23; /* direccion PIN B (registro de datos)*/

/* 
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * Poner en '0' el 5to bit de la dirección 0x24, que 
 * es el la dirección del registro de control
 * (direccion de los datos) del puerto B (DDRB - Data Direction Register).
 * El 5to bit define la entrada o salida del
 * pin del atmega328p que tiene conectado un led en una board arduino
 */

void led_init(void)
{
	volatile unsigned char *DDR_B = (unsigned char *)0x24;	// Direccion de DDRB
	volatile unsigned char *PORT_B = (unsigned char *)0x25; // Direccion de PORTB

	*PORT_B = *PORT_B & ~LED_ROJO; // Coloca 0 en el bit 5 de PORTB
	*DDR_B = *DDR_B | LED_ROJO;	   // Coloca 1 en el bit 5 de DDRB

	return;
}

void led_toggle(void)
{
	volatile unsigned char *PORT_B = (unsigned char *)0x25; // Direccion de PORTB
	unsigned char status;

	status = *PORT_B;			// status almacena el estado actual del led
	status = status ^ LED_ROJO; // cambia el status
	*PORT_B = status;			// vuelve a almacenar el status en el PORTB

	return;
}

void delay_ms(int milliseconds)
{
	volatile unsigned long cycles = milliseconds * CYCLES_PER_MS;

	while (cycles != 0)
	{
		cycles--;
	}

	return;
}