#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdbool.h>
#include "io.h"


pwm_input_t g_pwm_in_cntr;
pwm_input_t g_pwm_in;

bool g_looking_for_rising_edge;

void gpio_init(void)
{
  /* setup input pin */
  PORTB &= ~PWM_IN;
  DDRB &= ~PWM_IN;

  /* setup outputs */
  //PORTB |= _BV(0) | _BV(1) | _BV(3) | _BV(4);
  DDRB |= _BV(0) | _BV(1) | _BV(3) | _BV(4);

  GIMSK |= (1 << PCIE);   // PCNT interrupt enable
  PCMSK |= (1 << PCINT2);
  g_looking_for_rising_edge = true;

}

/* pin interrupt */
ISR(PCINT0_vect)
{
	cli();
	if(PINB & PWM_IN) {
		g_pwm_in_cntr.milliseconds = 0;
		g_pwm_in_cntr.microseconds = 0;
		TCNT0 = 0;
		MCUCR &= ~(1<<ISC00);
		g_looking_for_rising_edge = false;
//		PORTB |= _BV(1);
	} else {
		g_pwm_in.milliseconds = g_pwm_in_cntr.milliseconds;
		g_pwm_in.microseconds = g_pwm_in_cntr.microseconds;
		MCUCR |= (1<<ISC00);
		g_looking_for_rising_edge = true;
//		PORTB &= ~_BV(1);
	}
	sei();
}
