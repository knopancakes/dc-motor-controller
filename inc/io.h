#ifndef _IO_H_
#define _IO_H_

/* pwm input capture */
#define PWM_IN _BV(2)

typedef struct {
	uint32_t microseconds;
	uint32_t milliseconds;
} pwm_input_t;

extern pwm_input_t g_pwm_in_cntr;
extern pwm_input_t g_pwm_in;


//#define PWM_HI() { return PINB & PWM_IN; }

void gpio_init(void);

#endif // _IO_H_
