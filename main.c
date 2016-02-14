/* 
 * hall effect example
 * by will oberndorfer
 *
 * uses Melexis US5881 hall effect sensor
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define HALL_PIN PB0
#define LED_PIN PB1

volatile enum led_status { LED_OFF, LED_ON } led_flag;

/* interrupts when a pin change is detected on PB0 */
ISR(PCINT0_vect)
{
	if (bit_is_clear(PINB, HALL_PIN)) {
		led_flag = LED_ON;
	}
	else {
		led_flag = LED_OFF;
	}
}

int main(void)
{
	/* set initial state to off */
	led_flag = LED_OFF;
	
	/* set led pin for output, hall pin for input */
	DDRB |= (1 << LED_PIN);
	DDRB &= ~(1 << HALL_PIN);

	/* enable pull-up on hall pin */
	PORTB |= (1 << HALL_PIN);

	/* enable pcint0 */
	PCMSK0 |= (1 << PCINT0);
	PCICR |= (1 << PCIE0);
	sei();

	set_sleep_mode(SLEEP_MODE_IDLE);
	
	while (1) {
		/* go to sleep until interrupt */
		sleep_mode();

		/* turn led on or off based on flag set by interrupt */
		switch (led_flag) {
		case LED_OFF:
			PORTB &= ~(1 << LED_PIN);
			break;
		case LED_ON:
			PORTB |= (1 << LED_PIN);
			break;
		default:
			PORTB &= ~(1 << LED_PIN);
			break;
		}
	}

	return 0;	
}
