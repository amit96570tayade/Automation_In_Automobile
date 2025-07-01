#ifndef PWM_H
#define PWM_H

#include <LPC17xx.h>
#include <stdint.h>

#define PWM_CHANNEL   1
#define PWM_PERIOD    35000   // Adjust the PWM period based on your requirements

void PWM_Init(void);
void PWM_SetDutyCycle(uint32_t dutyCycle);

#endif
