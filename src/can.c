#include "can.h"

// Function to initialize CAN2 controller
void CAN2_Init(void) 
{
    // Set P2.7 as RD2 and P2.8 as TD2 CAN2 PINS
    LPC_PINCON->PINSEL4 |=  (1 << 14);
    LPC_PINCON->PINSEL4 &= ~(1 << 15);
    LPC_PINCON->PINSEL4 |=  (1 << 16);
    LPC_PINCON->PINSEL4 &= ~(1 << 17);
    
    // Enable power to CAN2 controller
    LPC_SC->PCONP |= (1 << 14);
    
    // Set CAN2 in Reset mode
    LPC_CAN2->MOD = 1;
    
    // Configure the Baud Rate for CAN2
    LPC_CAN2->BTR = (1 << 23) | (1 << 20) | (6 << 16) | (0X00); // CAN2 clock = PCLK/(0+1)= 1MHz/1=1000KHz  i.e Time Quanta = 1 us
                                                                // i.e total time quanta = 10us/1us = 10
                                                                // (1+TSEG1)/(1+TSEG1+TSEG2)= 80% => (1+TSEG1)/10 = 80% => TSEG1 = 7 and TSEG2 = 2
    // Set CAN2 in Normal mode
    LPC_CAN2->MOD = 0;
}

// Function to initialize CAN1 controller
void CAN1_Init(void) 
{
    // Set P0.0 as RD1 and P0.1 as TD1
    LPC_PINCON->PINSEL0 |=  (1 << 0);
    LPC_PINCON->PINSEL0 &= ~(1 << 1);
    LPC_PINCON->PINSEL0 |=  (1 << 2);
    LPC_PINCON->PINSEL0 &= ~(1 << 3);
    
    // Enable power to CAN1 controller
    LPC_SC->PCONP |= (1 << 13);
    
    // Set CAN1 in Reset mode
    LPC_CAN1->MOD = 1;
    
    // Configure the Baud Rate for CAN1
    LPC_CAN1->BTR = (1 << 23) | (1 << 20) | (6 << 16) | (0X00); // CAN1 clock = PCLK/(0+1)= 1MHz/1=1000KHz  i.e Time Quanta = 1 us
                                                                // i.e total time quanta = 10us/1us = 10
                                                                // (1+TSEG1)/(1+TSEG1+TSEG2)= 80% => (1+TSEG1)/10 = 80% => TSEG1 = 7 and TSEG2 = 2
    // Set CAN1 in Normal mode
    LPC_CAN1->MOD = 0;
}

// Function to receive a CAN message using CAN1 controller
void CAN1_MessageReceive(uint32_t *msgId, uint64_t *data, uint8_t *length) 
{
    // Wait until Receive Buffer (RBR) is not empty
    while ((LPC_CAN1->GSR & (1 << 0)) == 1) { }
    
    // Load the message ID to a variable
    *msgId = LPC_CAN1->RID;

    // Extract data length code from the frame status
    *length = (LPC_CAN1->RFS >> 16) & 0x0F;
    
    // Load the first 4 bytes of received data
    *data = LPC_CAN1->RDA;
    
    // If data length is greater than 4 bytes, load the next 4 bytes of data
    if (*length > 4)
    {
        *data = *data | ((uint64_t)LPC_CAN1->RDB << 32);
    }

    // Release the buffer
    LPC_CAN1->CMR = (1 << 2);
}

// Function to send a CAN message using CAN2 controller
void CAN2_MessageSend(uint32_t msgId, uint64_t data, uint8_t length) 
{
    // Wait until Transmit Buffer 1 (TBR1) is empty
    while ((LPC_CAN2->GSR & (1 << 2)) == 0) { }
    
    // Set the message ID
    LPC_CAN2->TID1 = msgId;
    
    // If extended message ID, set the Extended Identifier Flag
    if (msgId > 0x7FF)
    {
        LPC_CAN2->TFI1 |= (1U << 31);
    }

    // Set data length code
    LPC_CAN2->TFI1 |= ((uint32_t)length << 16);

    // If data length is greater than 4 bytes, set the first 4 bytes of data
    if (length > 4)
    {
        LPC_CAN2->TDB1 = data >> 32;
    }
    
    // Set the next 4 bytes of data
    LPC_CAN2->TDA1 = (uint32_t)data;
    
    // Enable queued transmission and select Tx Buffer1
    LPC_CAN2->CMR |= (1 << 0) | (1 << 5);
    
    // Wait for transmission completion
    while ((LPC_CAN2->GSR & (1 << 3)) == 0) { }
}
