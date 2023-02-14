#ifndef GENERIC_CANIO_H
#define GENERIC_CANIO_H

#include "Generic_CANIO_user.h"

typedef struct CANIO_Message
{
    uint32_t id;
    uint8_t len;
    uint8_t data[8];
}tst_CANIO_Msg;
typedef tst_CANIO_Msg (*CAN_Handler_Function)(tst_CANIO_Msg);
typedef struct CAN_Handler_ListEntry
{
    uint8_t MUX0;
    uint8_t CyclicPossible;        
    uint16_t CycleTimer_ms; // Wenn nicht null, dann wird der "Handler" mit einer "unvalid" CAN Message gestartet
    uint32_t CycleTimer_TS;
    uint16_t ExecCounter;
    CAN_Handler_Function Handler;
}tst_CAN_Handler_Entry;



extern tst_IO_List_Entry OutputList[];
extern tst_CAN_Handler_Entry CanHandlerList[];

void            Generic_CAN_Init(uint8_t Source_ID);
uint32_t        Generic_CAN_GetRxCANid(void);
tst_CANIO_Msg   Generic_CAN_HandleMessage(tst_CANIO_Msg CanRxMessage);
void            Generic_CAN_CycliqMessage(void);
int              Generic_CAN_SearchHandler(uint8_t MUX0);

#endif