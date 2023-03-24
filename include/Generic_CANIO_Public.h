#ifndef GENERIC_CANIO_PUBLIC_H
#define GENERIC_CANIO_PUBLIC_H

#include "Generic_CANIO_interface_SPU7066.h"





//############################################################# PUBLIC PIMARY CALL Funktionen #################################################################
void                Generic_CAN_Init                (uint8_t Source_ID);
tst_CANIO_Msg       Generic_CAN_HandleMessage       (tst_CANIO_Msg CanRxMessage);
void                Generic_CAN_CycliqMessage       (void);




//############################################################# GENERIC CAN Command List #################################################################
tst_CANIO_Msg CAN_0x00_CMD_PING             (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x01_SYS_BuildDate        (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x02_SYS_BuildTime        (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x03_SYS_SerNum           (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x04_SYS_SWversion        (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x05_SYS_BSPversion       (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x06_SYS_ProjectName      (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x10_INPUT_GET            (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x20_OUTPUT_SET           (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x21_OUTPUT_SAVESTATE     (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x22_OUTPUT_SWITCHOFF     (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0xA0_CMD_BAUDRATE         (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0xA1_CMD_SOURCE_ADR       (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0xA2_CMD_TX_CYCLE         (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0xA3_CMD_ERR_IGN          (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0xB0_CMD_PWM_CNF          (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0xD0_CMD_TaskHandle       (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0xD0_CMD_Errorbits        (tst_CANIO_Msg CanRxMessage);



//############################################################# PUBLIC LIB Funktionen #################################################################
int                 LIB_IO_GET_ListSize         (void);
int                 LIB_CAN_isValid             (tst_CANIO_Msg CanRXMessage);




#endif