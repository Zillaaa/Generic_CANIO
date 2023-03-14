#ifndef GENERIC_CANIO_USER_H
#define GENERIC_CANIO_USER_H

#include "Generic_CANIO\include\Generic_CANIO_Private.h"
#include "user_code.h"


//############################################################# PUBLIC HAL Funktionen #################################################################
ten_CanErrorList    HAL_IO_GET_Input            (uint8_t index, uint32_t *pReadValue);
ten_CanErrorList    HAL_IO_SET_Output           (uint8_t index, uint32_t newValue);
void                HAL_CAN_SendMsg             (tst_CANIO_Msg *Data); // main.cpp
bios_can_msg_typ    HAL_ConvertTo               (tst_CANIO_Msg Msg);
tst_CANIO_Msg       HAL_ConvertFrom             (bios_can_msg_typ Msg);
void                HAL_update_SourceID         (uint8_t newSourceID);
uint32_t            HAL_SYS_GET_Millis          (void);
void                HAL_SYS_Get_SerialNumber    (char* pString);
int                 HAL_WRITE_EEP               (void);




extern const char* pProjectName;
extern const char* pProjektVersion;
extern volatile uint8_t CANrxOverRun;
extern volatile uint8_t CANrxCounter;
extern volatile uint8_t CANtxCounter;
extern volatile uint8_t CANcmdCounter;
#endif