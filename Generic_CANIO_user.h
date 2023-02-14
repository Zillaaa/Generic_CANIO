#ifndef GENERIC_CANIO_USER_H
#define GENERIC_CANIO_USER_H


#include "user_code.h"

typedef enum CAN_ERROR_LIST
{
    CAN_ERR_OK,
    CAN_ERR_UNKOWN,
    CAN_ERR_NOTIMPLEMENTED,
    CAN_ERR_OUTOFRANGE,
    CAN_ERR_NOTFOUND,
    CAN_ERR_MAGICNUMBER_FAIL,
    CAN_ERR_UNSUPPORTED,
    CAN_ERR_INDEX_NOTFOUND,
    CAN_ERR_OUTPUT_DISABLED,
    CAN_ERR_EEP_PATTERNWRONG,
    CAN_ERR_EEP_CHECKSUMWRONG,
    CAN_ERR_INDEX_OUTOFRANGE,
}ten_CanErrorList;

typedef enum IO_List_Types
{
    IO_UNKOWN,
    IO_INPUT_MV,
    IO_INPUT_CURR,
    IO_OUTPUT_SW,
    IO_OUTPUT_PROM,
    IO_OUTPUT_CURR
}ten_IO_Type;

typedef struct IOConfigList
{
    ten_IO_Type IO_Type;
    uint8_t HAL_ID;    
    uint8_t Enabled;
    uint16_t SafeValue;
    uint16_t actualValue;    
    uint16_t actualValue_MIN;
    uint16_t actualValue_MAX;
    uint32_t actualValue_TS;    
    
}tst_IO_List_Entry;

uint32_t Generic_CAN_Switch_RXTX(uint32_t CanId);
uint32_t HAL_SYS_GET_Millis(void);
#endif