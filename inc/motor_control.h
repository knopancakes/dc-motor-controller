#ifndef _MOTOR_CONTROL_H_
#define _MOTOR_CONTROL_H_

#include <avr/io.h>

#define PWM_INPUT_MIN_US	1150.0f
#define PWM_INPUT_MAX_US	1950.0f

typedef union {
	struct {
		uint8_t kill : 1;
		uint8_t reverse : 1;
		uint8_t brake : 1;
		uint8_t rsvd : 5;
	};
	uint8_t bits;
} motor_status_t;

extern motor_status_t g_motor_status;

void motor_control_init();
void motor_control_state_machine();

#endif //_MOTOR_CONTROL_H_
