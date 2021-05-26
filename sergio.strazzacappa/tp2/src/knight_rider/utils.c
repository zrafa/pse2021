/*
 * PB5 = 13
 * PB4 = 12
 * PB3 = 11
 * PB2 = 10
 * PB1 = 9
 * PB0 = 8
 */

int led_bits[] = {
	0x01, // Bit 0 - 0000 0001
	0x02, // Bit 1 - 0000 0010
	// 0x04, // Bit 2 - 0000 0100
	0x08, // Bit 3 - 0000 1000
	0x10, // bit 4 - 0001 0000
	0x20  // bit 5 - 0010 0000
};

#define CYCLES_PER_MS (200);

void led_init(void)
{
	volatile unsigned char *DDR_B = (unsigned char *)0x24;
	volatile unsigned char *PORT_B = (unsigned char *)0x25;

	for (int i = 0; i < 2; i++)
	{
		*DDR_B = *DDR_B | led_bits[i];	  // Setea el bit i de DDRB a 1 (output)
		*PORT_B = *PORT_B & ~led_bits[i]; // Setea el bit i de PORTB a 0 (apaga)
	}

	return;
}

void led_toggle(int on, int off)
{
	volatile unsigned char *PORT_B = (unsigned char *)0x25;
	unsigned char status;

	status = *PORT_B;
	status = status ^ led_bits[on];

	if (off != -1)
	{
		status = status ^ led_bits[off];
	}

	*PORT_B = status;

	return;
}

void delay_ms(int milliseconds)
{
	volatile long long cycles = (long long)milliseconds * CYCLES_PER_MS;

	while (cycles != 0)
	{
		cycles--;
	}

	return;
}