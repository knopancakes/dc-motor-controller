#ifndef _IO_H_
#define _IO_H_

/* pwm input capture */
#define PWM_IN _BV(2);

//#define PWM_HI() { return PINB & PWM_IN; }

void pwm_in_init(void);

#endif // _IO_H_
