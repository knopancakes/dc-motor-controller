#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "io.h"
#include "timer.h"
#include "motor_control.h"


/* wrapper for all initialization calls */
void chip_init(void);

/* main routine */
int main(void)
{
  chip_init();
  motor_control_init();

  while(1)
    {
	  _delay_ms(1);
	  motor_control_state_machine();
    }

  return 0;

}

/* function definitions */
void chip_init(void)
{
	gpio_init();

	timer_init();

	/* interrupt enable */
	sei();
}
