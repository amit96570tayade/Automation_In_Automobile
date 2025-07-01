#include <lpc17xx.h>
#include "ldr.h"
#include <stdio.h>

void initTimer0(void)
{
    LPC_TIM0->CTCR = 0x0;
    LPC_TIM0->PR   = PRESCALE;
    LPC_TIM0->TCR  = 0x02;
}

void startTimer0(void)
{
    LPC_TIM0->TCR = 0x02;
    LPC_TIM0->TCR = 0x01;
}

unsigned int stopTimer0(void)
{
    LPC_TIM0->TCR = 0x00;
    return LPC_TIM0->TC;
}

void delayUS(unsigned int microseconds)
{
    LPC_TIM0->TCR = 0x02;
    LPC_TIM0->TCR = 0x01;
    while (LPC_TIM0->TC < microseconds);
    LPC_TIM0->TCR = 0x00;
}

void delayMS(unsigned int milliseconds)
{
    delayUS(milliseconds * 1000);
}

int adc_ldr_conv()
{
    int result = 0;
    LPC_SC->PCONP       |= ADC_CLK_EN_2;
    LPC_PINCON->PINSEL1 |= (1 << 16);             // select AD0.1 for P0.24
    LPC_ADC->ADCR        = ADCR_SETUP_SCM_2 | SEL_AD0_1_2;
    LPC_ADC->ADCR       |= START_CNV_2;           // Start new Conversion (Software controlled)
    
    while ((LPC_ADC->ADDR1 & ADC_DONE_2) == 0);
    
    result = (LPC_ADC->ADDR1 >> 4) & 0xFFF;        // 12-bit Mask to extract result
    return result;
}
