#ifndef LDR_H
#define LDR_H

// UART Definitions
#define RDR             (1 << 0)
#define THRE            (1 << 5)    // Transmit Holding Register Empty
#define MULVAL          15
#define DIVADDVAL       2
#define Ux_FIFO_EN      (1 << 0)
#define Rx_FIFO_RST     (1 << 1)
#define Tx_FIFO_RST     (1 << 2)
#define DLAB_BIT        (1 << 7)
#define LINE_FEED       0x0A        // LF, for Linux, MAC and Windows Terminals  
#define CARRIAGE_RETURN 0x0D        // CR, for Windows Terminals (CR+LF)

// ADC Definitions
#define ADC_CLK_EN_2    (1 << 12)
#define SEL_AD0_1_2     (1 << 1)    // Select Channel AD0.1 
#define CLKDIV_2        1           // ADC_CLOCK = PCLK / (CLKDIV + 1) = 12.5MHz @ 25MHz PCLK
#define PWRUP_2         (1 << 21)   // Setting to 0 powers down ADC
#define START_CNV_2     (1 << 24)   // Start conversion immediately
#define ADC_DONE_2      (1U << 31)  // Unsigned to prevent compiler warning
#define ADCR_SETUP_SCM_2 ((CLKDIV_2 << 8) | PWRUP_2)

// Timer Definitions
#define PRESCALE        (25 - 1)

// Function Prototypes
void initUART0(void);
void initTimer0(void);
void startTimer0(void);
unsigned int stopTimer0(void);
void delayUS(unsigned int microseconds);
void delayMS(unsigned int milliseconds);
void U0Write(char data);
char U0Read(void);
int adc_ldr_conv(void);

#endif
