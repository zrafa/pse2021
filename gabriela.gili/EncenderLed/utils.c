/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

void init(void){
	
	volatile unsigned char * DDRB = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
	volatile unsigned char * PORTB = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
	*PORTB =*PORTB & ~LED_ROJO; 
	*DDRB  = DDRB | LED_ROJO;  
    return; 
}


void toggle (void) {
	volatile unsigned char * PORTB = (unsigned char *) 0x25; 
	unsigned char e;
	/* delay de 1 segundo */
	e=*PORTB;
	e= e ^ LED_ROJO;
	*PORTB= e;
        return; 
}

void delay(int ms) {
	volatile long long i = (long long)milliseconds*CYCLES_PER_MS;
	while(i!=0){
		i--;
	}
	return;
}

