#include "pwm.h"

void PWM_Init(void) {
    // Enable PWM1 peripheral clock
    LPC_SC->PCONP |= (1 << 6);

    // Configure P2.0 as PWM1.1 (adjust pin based on your connections)
    LPC_PINCON->PINSEL4 &= ~(3 << 0);
    LPC_PINCON->PINSEL4 |=  (1 << 0);

    // Set PWM mode and timer mode
    LPC_PWM1->CTCR = 0x00;         // Timer Mode
    LPC_PWM1->MCR  = (1 << 1);     // Reset on MR1

    // Set the PWM period
    LPC_PWM1->PR   = 0;                           // Prescaler
    LPC_PWM1->MR0  = PWM_PERIOD - 1;              // Match Register 0

    // Set initial duty cycle to 50%
    LPC_PWM1->MR1  = PWM_PERIOD / 2;

    // Enable PWM1 output
    LPC_PWM1->PCR |= (1 << 9);     // PWM1 output enabled

    // Enable PWM Timer Counter and PWM Mode
    LPC_PWM1->TCR = (1 << 0) | (1 << 3);
}

void PWM_SetDutyCycle(uint32_t dutyCycle) {
    // Set the duty cycle for PWM1
    LPC_PWM1->MR1 = dutyCycle;
    
    // Update the match register with the new duty cycle
    LPC_PWM1->LER = (1 << 1);  // Enable shadow register for MR1
}
