#ifndef _TIMER_H_
#define _TIMER_H_

/**
 * Clock division by 16 -> 500Khz
 * target 2Khz / 500Khz = 250
 * Clock gets n-1
 */
#define TIMER_TOP_2KHZ 249

void timer_init();

#endif //_TIMER_H_
