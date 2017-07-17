#include <avr/io.h>
#include <string.h>
#include <stdbool.h>
#include "motor_control.h"
#include "timer.h"
#include "io.h"

motor_status_t g_motor_status;

void
motor_control_init()
{
	memset(&g_motor_status, 0, sizeof(g_motor_status));
	memset(&g_pwm_in, 0, sizeof(g_pwm_in));
	memset(&g_pwm_in_cntr, 0, sizeof(g_pwm_in_cntr));
}

void
motor_control_state_machine()
{
	// TODO add brakes / reverse
	uint8_t pwm_out;
	float pwm_in_total_us;
	float tmp;

	/**
	 * RC Timeout
	 */
	if( g_pwm_in_cntr.milliseconds >= 250) {
		g_motor_status.kill = true;
	} else {
		g_motor_status.kill = false; // TODO this might make bugs
	}

	/**
	 * Kill safety
	 */
	if(g_motor_status.kill) {
		pwm_out = 0;
		OCR1A = 0;
		OCR1B = 0;
		PORTB &= ~(_BV(0) | _BV(3));
	} else {

		/**
		 * calculate throttle percentage
		 */

		pwm_in_total_us = g_pwm_in.microseconds + (100 * g_pwm_in.milliseconds);

//		if( pwm_in_total_us < PWM_INPUT_MIN_US ) {
//			pwm_out = 0;
//		} else if ( pwm_in_total_us > PWM_INPUT_MAX_US) {
//			pwm_out = TIMER_TOP_2KHZ;
//		} else {
			tmp = pwm_in_total_us - PWM_INPUT_MIN_US;
			tmp /= PWM_INPUT_MAX_US - PWM_INPUT_MIN_US;
			pwm_out = (uint8_t)(TIMER_TOP_2KHZ*tmp);
//		}



		if(g_motor_status.brake) {
			OCR1A = 0;
			OCR1B = 0;
			PORTB |= _BV(0) | _BV(3);
		} else if(g_motor_status.reverse ) {
			OCR1B = pwm_out;
			OCR1A = 0;
			PORTB &= ~(_BV(0) | _BV(3));
		} else {
			OCR1A = pwm_out;
			OCR1B = 0;
			PORTB &= ~(_BV(0) | _BV(3));
		}
	}

}
