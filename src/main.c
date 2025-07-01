#include <LPC17xx.h>
#include <stdio.h>
#include <stdint.h>
#include "lcd.c"
#include "adc.c"
#include "can.c"
#include "pwm.c"
#include "ldr.c"

#define LDR_CUT_OFF     1800
#define CAN2_BAUD_RATE  100000
#define CAN1_BAUD_RATE  100000

int main(void)
{
    int result;

    uint32_t tmsgId = 0x123;
    float temp = 0;
    uint8_t tlength = 3;

    uint32_t rmsgId;
    uint64_t rmessageData;
    uint8_t rlength;

    char id_data[20];

    initTimer0();
    lcd_init();
    CAN2_Init();
    CAN1_Init();
    PWM_Init();

    LPC_GPIO1->FIODIR |= (0xFF << 19);
    LPC_GPIO1->FIOCLR |= (0xFF << 19);

    while (1)
    {
        temp = adc_conv();
        result = adc_ldr_conv();

        CAN2_MessageSend(tmsgId, (uint64_t)temp, tlength);
        CAN1_MessageReceive(&rmsgId, &rmessageData, &rlength);

        lcd_cmd_write(0x80);
        sprintf(id_data, "Temperature : %llu", rmessageData);
        lcd_str_write(id_data);

        // PWM_SetDutyCycle(rmessageData * 1000);
        // delay(100);

        if (rmessageData <= 28)
        {
            PWM_SetDutyCycle(10000);
        }

        if (rmessageData > 28)
        {
            PWM_SetDutyCycle(35000);
        }

        if (result < LDR_CUT_OFF)
        {
            LPC_GPIO1->FIOSET |= (0xFF << 19);
        }
        else
        {
            LPC_GPIO1->FIOCLR |= (0xFF << 19);
        }

        delayMS(50);
    }
}
