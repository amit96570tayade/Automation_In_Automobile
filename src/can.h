#ifndef CAN_H
#define CAN_H

#include <LPC17xx.h>
#include <stdint.h>

void CAN2_Init(void);
void CAN1_Init(void);

void CAN2_MessageSend(uint32_t msgId, uint64_t data, uint8_t length);
void CAN1_MessageReceive(uint32_t *msgId, uint64_t *data, uint8_t *length);

#endif
