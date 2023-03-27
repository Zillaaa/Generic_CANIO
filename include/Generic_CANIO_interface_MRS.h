#ifndef GENERIC_CANIO_INTERFACE_H
#define GENERIC_CANIO_INTERFACE_H


// Include User Libs here
#include "user_code.h"

//typedef TU8 uint8_t;
//typedef TU16 uint16_t;
//typedef TU32 uint32_t;
//typedef TS8 int8_t;
//typedef TS16 int16_t;
//typedef TS32 int32_t;
typedef bios_can_msg_typ sys_can_msg_t;

typedef enum IO_List_Types
{
    IO_UNKOWN,
    IO_INPUT_MV,
    IO_INPUT_CURR,
    IO_OUTPUT_SW,
    IO_OUTPUT_PROM,
    IO_OUTPUT_CURR
}ten_IO_Type;
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
    CANIO_ERR_INDEX_NOT_OUTPUT,
    CANIO_ERR_IOTYPE_DIFFERENT,
    CANIO_ERR_VALUE_OUTOFRANGE_MAX,
    CANIO_ERR_VALUE_OUTOFRANGE_MIN,
    CANIO_ERR_READ_FAIL,
    CANIO_ERR_TX_FAIL,
    CANIO_ERR_WRITE_FAIL,
    CANIO_ERR_NOT_POPULATED,
    CANIO_ERR_BAD_PARAMETER,
    CANIO_ERR_SEE_DEBUG
}ten_CanErrorList;

typedef struct CANIO_Message
{
    uint32_t id;
    uint8_t len;
    uint8_t data[8];
}tst_CANIO_Msg;

typedef tst_CANIO_Msg (*CAN_Handler_Function)(tst_CANIO_Msg);

typedef struct IOConfigList
{
    ten_IO_Type IO_Type;
    uint8_t HAL_ID;    
    uint8_t isEnabled;
    uint8_t isOutput;
    uint32_t SafeValue;
    uint32_t actualValue;    
    uint32_t actualValue_MAX ;
    uint32_t actualValue_MIN;
    uint32_t actualValue_TS;    
    void* pCustomData;
}tst_IO_List_Entry;

extern tst_IO_List_Entry GenericIOList[];
extern const tst_IO_List_Entry GenericIOList_DEFAULT[];
extern const size_t GenericIOList_sizeof;

typedef struct CAN_Handler_ListEntry
{
    uint8_t MUX0;
    uint8_t CyclicPossible;        
    uint16_t CycleTimer_ms; // Wenn nicht null, dann wird der "Handler" mit einer "unvalid" CAN Message gestartet
    uint32_t CycleTimer_TS;
    uint16_t ExecCounter;
    CAN_Handler_Function Handler;
}tst_CAN_Handler_Entry;


extern tst_CAN_Handler_Entry CanHandlerList[];



//############################################################# PUBLIC HAL Funktionen #################################################################
ten_CanErrorList    HAL_IO_GET_Input_mV         (uint8_t IOIndex, uint32_t *pValue);
ten_CanErrorList    HAL_IO_GET_Input_mA         (uint8_t IOIndex, uint32_t *pValue);
ten_CanErrorList    HAL_IO_GET_Output_ppm       (uint8_t IOIndex, uint32_t *pValue);
ten_CanErrorList    HAL_IO_GET_Output_bool      (uint8_t IOIndex, uint32_t *pValue);
ten_CanErrorList    HAL_IO_GET_Output_mA        (uint8_t IOIndex, uint32_t *pValue);
ten_CanErrorList    HAL_IO_SET_Input_mV         (uint8_t IOIndex, uint32_t pValue);
ten_CanErrorList    HAL_IO_SET_Input_mA         (uint8_t IOIndex, uint32_t pValue);
ten_CanErrorList    HAL_IO_SET_Output_ppm       (uint8_t IOIndex, uint32_t pValue);
ten_CanErrorList    HAL_IO_SET_Output_bool      (uint8_t IOIndex, uint32_t pValue);
ten_CanErrorList    HAL_IO_SET_Output_mA        (uint8_t IOIndex, uint32_t pValue);
ten_CanErrorList    HAL_IO_GET_Input            (uint8_t index, ten_IO_Type IO_Type, uint32_t *pReadValue);
ten_CanErrorList    HAL_IO_SET_Output           (uint8_t index, ten_IO_Type IO_Type, uint32_t newValue);
ten_CanErrorList    HAL_CAN_SendMsg             (tst_CANIO_Msg *Data); // main.cpp
ten_CanErrorList    HAL_ConvertTo               (tst_CANIO_Msg Msg, sys_can_msg_t* pDest);
ten_CanErrorList    HAL_ConvertFrom             (sys_can_msg_t Msg, tst_CANIO_Msg* pDest);
ten_CanErrorList    HAL_update_SourceID         (uint8_t newSourceID);
uint32_t            HAL_SYS_GET_Millis          (void);
void                HAL_SYS_Get_SerialNumber    (char*, size_t);
void                HAL_SYS_Get_ProjektVersion  (char*, size_t);
void                HAL_SYS_Get_pProjectName    (char*, size_t);
void                HAL_SYS_Get_pBSPversion     (char*, size_t);
ten_CanErrorList    HAL_WRITE_EEP               (void);

//############################################################# USER CAN Command List #################################################################
// In den Lücken zwischen den "fixierten CMDS" oben, können eigene CAN Nachrichten eingefügt werden.
tst_CANIO_Msg CAN_0x11_INPUT_GET_Generic        (tst_CANIO_Msg CanRxMessage);
tst_CANIO_Msg CAN_0x30_OUTPUT_GETCURR_Generic   (tst_CANIO_Msg CanRxMessage);



#endif