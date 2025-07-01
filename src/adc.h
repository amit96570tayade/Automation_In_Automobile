#ifndef ADC_H
#define ADC_H

#include <LPC17xx.h>
#include <stdint.h>

#define VREF        3.3f         // Reference Voltage at VREFP pin, VREFN = 0V (GND)
#define ADC_CLK_EN  (1 << 12)    // Enable ADC peripheral clock
#define SEL_AD0_2   (1 << 2)     // Select channel AD0.2 (P0.25)
#define CLKDIV      (3 << 8)     // ADC clock divider (ADC_CLOCK = PCLK / (CLKDIV + 1)) = 1 MHz @ 4 MHz PCLK
#define PWRUP       (1 << 21)    // Power up ADC (0 = power down)
#define START_CNV   (1 << 24)    // Start conversion immediately
#define ADC_DONE    (1U << 31)   // ADC done bit (use unsigned to avoid warning)
#define T_COEFF     100.0f       // Temperature coefficient (V to °C conversion factor)

#endif // ADC_H
