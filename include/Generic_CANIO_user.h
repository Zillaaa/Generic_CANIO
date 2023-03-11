#ifndef GENERIC_CANIO_USER_H
#define GENERIC_CANIO_USER_H


#include <Arduino.h>
#include <can_common.h>

typedef enum CANIO_ERROR_LIST
{
    CANIO_ERR_OK,
    CANIO_ERR_UNKOWN,
    CANIO_ERR_NOTIMPLEMENTED,
    CANIO_ERR_OUTOFRANGE,
    CANIO_ERR_NOTFOUND,
    CANIO_ERR_MAGICNUMBER_FAIL,
    CANIO_ERR_UNSUPPORTED,
    CANIO_ERR_INDEX_NOTFOUND,
    CANIO_ERR_OUTPUT_DISABLED,
    CANIO_ERR_EEP_PATTERNWRONG,
    CANIO_ERR_EEP_CHECKSUMWRONG,
    CANIO_ERR_INDEX_OUTOFRANGE,
    CANIO_ERR_INDEX_NOT_OUTPUT
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