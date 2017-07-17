#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "io.h"
#include "motor_control.h"

void
timer_init()
{
	/**
	 * 8 MHz Sys Clock
	 * OCR0A init to run timer at 100kHz
	 */
	OCR0A  = 79;       // number to count up to
	TIMSK |= (1 << OCIE0A);       // TC0 compare match A interrupt enable
	TCCR0A |= (1 << WGM01); // CTC
	TCCR0B = 0x01;      // clock source CLK/1, start timer

	/**
	 * 8 MHz Sys Clock
	 * OCR1A init
	 */
	TCCR1 |= (0 << COM1A1) | (1 << COM1A0); // connect to inverting and non inverting pins
	TCCR1 |= (0 << CS13 ) | (1 << CS12 ) |  (0 << CS11 ) |  (1 << CS10 ); // divide by 16
	TCCR1 |= (1 << PWM1A); // PWM mode enable
	GTCCR |= (0 << COM1B1) | (1 << COM1B0); // connect to inverting and non inverting pins
	GTCCR |= (1 << PWM1B); // PWM mode enable
	OCR1C = TIMER_TOP_2KHZ;
	OCR1A = 0;
	OCR1B = 0;

	/**
	 * Dead Time Selection
	 */
	DTPS1 = 1<<DTPS11 | 1<<DTPS10;
	//DT1A = 1<<DT1AH3 | 1<<DT1AH2 | 1<<DT1AH1 | 1<<DT1AH0 | 1<<DT1AL3 | 1<<DT1AL2 | 1<<DT1AL1 | 1<<DT1AL0;
	DT1A = 0;

	g_pwm_in_cntr.microseconds = 0;
	g_pwm_in_cntr.milliseconds = 0;
}


// interrupt service routine (ISR) for timer 0 A compare match
ISR(TIM0_COMPA_vect)
{
	cli();
	g_pwm_in_cntr.microseconds += 10;
	if(g_pwm_in_cntr.microseconds >= 100) {
		if(++g_pwm_in_cntr.milliseconds >= 2000) {
			g_pwm_in_cntr.milliseconds = 2000;
		}
		g_pwm_in_cntr.microseconds = 0;
//		PORTB ^= _BV(1);
	}

	sei();
}
