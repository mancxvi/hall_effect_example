/* 
 * hall effect test
 * by will oberndorfer
 *
 * uses Melexis US5881 hall effect sensor
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define HALL_PIN PB0
#define LED_PIN PB1

int main(void)
{
	/* set led pin for output, hall pin for input */
	DDRB |= (1 << LED_PIN);
	DDRB &= ~(1 << HALL_PIN);

	/* enable pull-up on hall pin */
	PORTB |= (1 << HALL_PIN);

	while (1) {
		
	}

	return 0;	
}

ISR(PCINT0_vect)
{
	if (bit_is_clear(PINB, HALL_PIN)) {
		PORTB |= (1 << LED_PIN);
	}
	else {
		PORTB &= ~(1 << LED_PIN);
	}
}
