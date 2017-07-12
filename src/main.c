#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "io.h"

/* wrapper for all initialization calls */
void chip_init(void);

/* main routine */
int main(void)
{
  
  chip_init();

  while(1)
    {

    }

  return 0;

}

/* function definitions */
void chip_init(void)
{
	pwm_in_init();

}
