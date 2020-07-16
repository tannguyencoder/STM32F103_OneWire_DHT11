#ifndef HC_SR04_H_
#define HC_SR04_H_

#include "includes.h"

#define US_TIMER					TIM3

#define US_TRIG_PORT				GPIOB
#define US_TRIG_PIN					GPIO_Pin_0		//(trig output):TIM Ch3 

#define US_ECHO_PORT				GPIOA
#define US_ECHO_PIN					GPIO_Pin_6		//(echo input):TIM Ch1 

#define US_TIMER_TRIG_SOURCE		TIM_TS_TI1FP1

/**
 *	How to use:

 *	1. Call HCSR04_Init();
 *	2. Get distance (in mm) using HCSR04_GetDistance function.
 *		Value lower than zero means no echo received (distance >3m)
 *		Measuring takes about 65ms
 *
 *	 US_ECHO_PIN must be tim ch1
 *	 and US_TRIG_PIN must be ch3 or ch4.
 */



/**
 * Initialization of HCSR04's peripherals
 */
void HCSR04_Init(void);

/**
 * get value in mm. Lower than 0 means no echo signal: distance more than ~3m.
 */
u16 HCSR04_GetDistance(void);

#endif /* HC_SR04_H_ */
