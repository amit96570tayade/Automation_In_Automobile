#include "adc.h"

float adc_conv()
{
    int result = 0;
    float volts = 0;
    float temp = 0;

    LPC_PINCON->PINSEL1 |= (0x01 << 18);           // Select AD0.2 for P0.25
    LPC_SC->PCONP |= ADC_CLK_EN;                   // Enable ADC clock

    LPC_ADC->ADCR = PWRUP | CLKDIV | SEL_AD0_2;
    LPC_ADC->ADCR |= START_CNV;                    // Start new conversion

    while ((LPC_ADC->ADDR2 & ADC_DONE) == 0) {}    // Wait until conversion is finished

    result = (LPC_ADC->ADDR2 >> 4) & 0xFFF;         // 12-bit mask to extract result
    volts = (result * VREF) / 4096.0;               // Convert result to voltage
    temp = volts * T_COEFF;                         // Convert voltage to temperature

    return temp;
}
