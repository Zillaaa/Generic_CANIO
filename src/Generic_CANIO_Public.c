

#include "Generic_CANIO_Public.h"
#include "Generic_CANIO_Private.h"
#define CAN_ID_MUX_0X22_MAGIC       57411
#define CAN_ID_MUX_0X21_MAGIC       8874
#define CAN_ID_MUX_0X20_MAGIC       56344
#define SYSTEM_CANIO_TX_CYCLE_MIN 100
#define SYSTEM_CANIO_TX_CYCLE_MAX 60000

// DEBUG:


//############################################################# IO Handling #################################################################
ten_CanErrorList    HAL_IO_GET_Input            (uint8_t index, ten_IO_Type IO_Type, uint32_t *pReadValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    uint32_t readValue = 0;
    if(index >= LIB_IO_GET_ListSize())                      return CANIO_ERR_INDEX_OUTOFRANGE;
    if(GenericIOList[index].IO_Type != IO_Type)             return CANIO_ERR_IOTYPE_DIFFERENT;

    switch(GenericIOList[index].IO_Type)
    {
        default: result = CANIO_ERR_UNSUPPORTED; break;
        case IO_INPUT_MV:       result = HAL_IO_GET_Input_mV     (index, &readValue); break;
        case IO_INPUT_CURR:     result = HAL_IO_GET_Input_mA     (index, &readValue); break;
        case IO_OUTPUT_PROM:    result = HAL_IO_GET_Output_ppm   (index, &readValue); break;
        case IO_OUTPUT_SW:      result = HAL_IO_GET_Output_bool  (index, &readValue); break;
        case IO_OUTPUT_CURR:    result = HAL_IO_GET_Output_mA    (index, &readValue); break;
        
    }

    if(result == CANIO_ERR_OK)
    {
        if(readValue > GenericIOList[index].actualValue_MAX) readValue = GenericIOList[index].actualValue_MAX;
        if(readValue < GenericIOList[index].actualValue_MIN) readValue = GenericIOList[index].actualValue_MIN;
        GenericIOList[index].actualValue = readValue;
        GenericIOList[index].actualValue_TS = HAL_SYS_GET_Millis();
        *pReadValue = readValue;
    }

    return result;
}
ten_CanErrorList    HAL_IO_SET_Output           (uint8_t index, ten_IO_Type IO_Type, uint32_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(index >= LIB_IO_GET_ListSize())                          return CANIO_ERR_INDEX_OUTOFRANGE;        
    
    if(GenericIOList[index].IO_Type != IO_Type)                 return CANIO_ERR_IOTYPE_DIFFERENT;
    if(GenericIOList[index].isOutput == 0)                      return CANIO_ERR_INDEX_NOT_OUTPUT; 
    if(GenericIOList[index].isEnabled == 0)                     return CANIO_ERR_OUTPUT_DISABLED;
    if(GenericIOList[index].actualValue_MIN > newValue)         return CANIO_ERR_VALUE_OUTOFRANGE_MIN;
    if(GenericIOList[index].actualValue_MAX < newValue)         return CANIO_ERR_VALUE_OUTOFRANGE_MAX;

    switch(GenericIOList[index].IO_Type)
    {
        default: result = CANIO_ERR_UNSUPPORTED; break;
        case IO_OUTPUT_PROM:    result = HAL_IO_SET_Output_ppm   (index, newValue); break;
        case IO_OUTPUT_SW:      result = HAL_IO_SET_Output_bool  (index, newValue); break;
        case IO_OUTPUT_CURR:    result = HAL_IO_SET_Output_mA    (index, newValue); break;
        
        
    }
    if(result == CANIO_ERR_OK)
    {
        GenericIOList[index].actualValue = newValue;
        GenericIOList[index].actualValue_TS = HAL_SYS_GET_Millis();        
    }

    
    
    return result;
}


//############################################################# GENERIC CAN Command List #################################################################
// Dies sind die fixierten CMDs, deren Inhalt beibehalten und gefüllt werden müssen.

tst_CANIO_Msg CAN_0x00_CMD_PING(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = (uint8_t) (HAL_SYS_GET_Millis() / 1000);     
    CanTxMessage.data[2] = Generic_CAN_rxCounter; 
    CanTxMessage.data[3] = Generic_CAN_txCounter; 
    CanTxMessage.data[4] = Generic_CAN_rxOverFlow;
    CanTxMessage.data[5] = Generic_CAN_txOverFlow;
    CanTxMessage.data[6] = Generic_CAN_cmdCounter;
    CanTxMessage.data[7] = 0;                                           //tbd
    

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x01_SYS_BuildDate(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_CAN_PrintString(&CanTxMessage, __DATE__)) if(HAL_CAN_SendMsg(&CanTxMessage)) Generic_CAN_txOverFlow++;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x02_SYS_BuildTime(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_CAN_PrintString(&CanTxMessage, __TIME__)) if(HAL_CAN_SendMsg(&CanTxMessage)) Generic_CAN_txOverFlow++;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x03_SYS_SerNum(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    char Buffer[10];
    HAL_SYS_Get_SerialNumber(Buffer, sizeof(Buffer));
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;

    

    while(LIB_CAN_PrintString(&CanTxMessage, Buffer)) if(HAL_CAN_SendMsg(&CanTxMessage)) Generic_CAN_txOverFlow++;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x04_SYS_SWversion(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    char Buffer[30];
    HAL_SYS_Get_ProjektVersion(Buffer, sizeof(Buffer));

    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_CAN_PrintString(&CanTxMessage, (const char*)Buffer)) if(HAL_CAN_SendMsg(&CanTxMessage)) Generic_CAN_txOverFlow++;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x05_SYS_BSPversion(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    char Buffer[30];
    HAL_SYS_Get_pBSPversion(Buffer, sizeof(Buffer));

    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_CAN_PrintString(&CanTxMessage, Buffer)) if(HAL_CAN_SendMsg(&CanTxMessage)) Generic_CAN_txOverFlow++;

    
    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x06_SYS_ProjectName(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    char Buffer[30];
    HAL_SYS_Get_pProjectName(Buffer, sizeof(Buffer));

    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_CAN_PrintString(&CanTxMessage, Buffer)) if(HAL_CAN_SendMsg(&CanTxMessage)) Generic_CAN_txOverFlow++;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x10_INPUT_GET(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    ten_IO_Type IO_Type = 0;
    uint32_t InputValue = 0;    
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // IOType

    IO_Selector = CanTxMessage.data[1];
    IO_Type = (ten_IO_Type) CanTxMessage.data[2];

    result = (uint8_t)HAL_IO_GET_Input(IO_Selector, IO_Type, &InputValue);    
    CanTxMessage.data[3] = (uint8_t) (InputValue >> 0);
    CanTxMessage.data[4] = (uint8_t) (InputValue >> 8);
    CanTxMessage.data[5] = (uint8_t) (InputValue >> 16);
    CanTxMessage.data[6] = (uint8_t) (InputValue >> 24);
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x20_OUTPUT_SET(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    ten_IO_Type IO_Type = 0;
    uint16_t NewValue = 0;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // IOType
    CanTxMessage.data[2] = CanRxMessage.data[2]; // NewValue
    CanTxMessage.data[3] = CanRxMessage.data[3]; // NewValue
    CanTxMessage.data[4] = CanRxMessage.data[4]; // MagicNumber
    CanTxMessage.data[5] = CanRxMessage.data[5]; // MagicNumber

    IO_Selector = CanTxMessage.data[1];
    IO_Type = (ten_IO_Type) CanTxMessage.data[2];

    NewValue = (uint16_t)(((uint32_t) CanRxMessage.data[3] << 0) + ((uint32_t) CanRxMessage.data[4] << 8));
    MagicNumber = (uint16_t)(((uint32_t) CanRxMessage.data[5] << 0) + ((uint32_t) CanRxMessage.data[6] << 8));

    if(MagicNumber == CAN_ID_MUX_0X20_MAGIC)
    {
        result= (uint8_t) HAL_IO_SET_Output(IO_Selector, IO_Type, NewValue);        
    } 
    else result = CANIO_ERR_MAGICNUMBER_FAIL;
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x21_OUTPUT_SAVESTATE(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    ten_IO_Type IO_Type = 0;
    uint16_t SafeStateValue = 0;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // IOType
    CanTxMessage.data[3] = CanRxMessage.data[3]; // SafeState
    CanTxMessage.data[4] = CanRxMessage.data[4]; // SafeState
    CanTxMessage.data[5] = CanRxMessage.data[5]; // MagicNumber
    CanTxMessage.data[6] = CanRxMessage.data[6]; // MagicNumber
    

    IO_Selector = CanTxMessage.data[1];
    IO_Type = (ten_IO_Type) CanTxMessage.data[2];
    SafeStateValue = (uint16_t)(((uint32_t) CanRxMessage.data[2] << 0) + ((uint32_t) CanRxMessage.data[3] << 8));
    MagicNumber = (uint16_t)(((uint32_t) CanRxMessage.data[4] << 0) + ((uint32_t) CanRxMessage.data[5] << 8));

    if(MagicNumber == CAN_ID_MUX_0X21_MAGIC)
    {
        if(IO_Selector < LIB_IO_GET_ListSize()) CanTxMessage.data[7] = (uint8_t) LIB_IO_SET_Output_Safe(IO_Selector, IO_Type, SafeStateValue);
        else                                    CanTxMessage.data[7] = CANIO_ERR_INDEX_NOTFOUND;
    } 
    else result = CANIO_ERR_MAGICNUMBER_FAIL;
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x22_OUTPUT_SWITCHOFF(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    ten_IO_Type IO_Type = 0;
    uint8_t NewValue;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // NewValue
    CanTxMessage.data[3] = CanRxMessage.data[3]; // MagicNumber
    CanTxMessage.data[4] = CanRxMessage.data[4]; // MagicNumber

    IO_Selector =                           CanTxMessage.data[1];
    IO_Type     = (ten_IO_Type)             CanTxMessage.data[2];
    NewValue    =                           CanTxMessage.data[2];
    MagicNumber = (uint16_t)(((uint32_t)    CanRxMessage.data[3] << 0) + ((uint32_t) CanRxMessage.data[4] << 8));

    if(MagicNumber == CAN_ID_MUX_0X22_MAGIC)
    {
        if(IO_Selector < LIB_IO_GET_ListSize()) CanTxMessage.data[7] = (uint8_t) LIB_IO_SET_Output_Enable(IO_Selector, IO_Type, NewValue ? 1 : 0);
        else                                    CanTxMessage.data[7] = CANIO_ERR_INDEX_NOTFOUND;
    } 
    else result = CANIO_ERR_MAGICNUMBER_FAIL;
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0xA0_CMD_BAUDRATE(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[7] = CANIO_ERR_NOTIMPLEMENTED;
    return CanTxMessage;
}
tst_CANIO_Msg CAN_0xA1_CMD_SOURCE_ADR(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // New Source Adress

    if((CanRxMessage.data[1] > 0) && (CanRxMessage.data[1] < 0xFF))
    {
        
        HAL_update_SourceID(CanRxMessage.data[1]);        
        CanTxMessage.data[7] = (uint8_t) HAL_WRITE_EEP();        
    }
    else    CanTxMessage.data[7] = CANIO_ERR_OUTOFRANGE;
    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0xA2_CMD_TX_CYCLE(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    uint8_t Selector = 0;
    uint16_t CycleTimer_ms = 0;
    int index = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // Selection
    CanTxMessage.data[2] = CanRxMessage.data[2]; // ms
    CanTxMessage.data[3] = CanRxMessage.data[3]; // ms

    Selector = CanTxMessage.data[1];
    CycleTimer_ms = (uint16_t) (((uint32_t) CanRxMessage.data[2] << 0) + ((uint32_t) CanRxMessage.data[3] << 8));

    index = LIB_CAN_SearchHandler(Selector);

    if(index >= 0)
    {
        if((CycleTimer_ms >= SYSTEM_CANIO_TX_CYCLE_MIN) && (CycleTimer_ms <= SYSTEM_CANIO_TX_CYCLE_MAX))
        {
            CanHandlerList[index].CycleTimer_ms = CycleTimer_ms;            
            CanHandlerList[index].CyclicPossible = 1;
            CanTxMessage.data[7] = (uint8_t) HAL_WRITE_EEP();
        }
        else CanTxMessage.data[7] = CANIO_ERR_OUTOFRANGE;
    }
    else CanTxMessage.data[7] = CANIO_ERR_OUTOFRANGE;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0xA3_CMD_ERR_IGN(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // Toggle Ignore ID
    CanTxMessage.data[2] = CanRxMessage.data[2]; // Toggle Ignore ID
    CanTxMessage.data[3] = CanRxMessage.data[3]; // Toggle Ignore ID
    CanTxMessage.data[4] = CanRxMessage.data[4]; // Toggle Ignore ID
    CanTxMessage.data[5] = CanRxMessage.data[5]; // Toggle Ignore ID
    CanTxMessage.data[6] = CanRxMessage.data[6]; // Toggle Ignore ID

    /*

    if(CanTxMessage.data[1] < ERR_CNT) ErrorList[CanTxMessage.data[1]].Ignore = ErrorList[CanTxMessage.data[1]].Ignore ? 0 : 1; else result = 0;
    if(CanTxMessage.data[2] < ERR_CNT) ErrorList[CanTxMessage.data[2]].Ignore = ErrorList[CanTxMessage.data[2]].Ignore ? 0 : 1; else result = 0;
    if(CanTxMessage.data[3] < ERR_CNT) ErrorList[CanTxMessage.data[3]].Ignore = ErrorList[CanTxMessage.data[3]].Ignore ? 0 : 1; else result = 0;
    if(CanTxMessage.data[4] < ERR_CNT) ErrorList[CanTxMessage.data[4]].Ignore = ErrorList[CanTxMessage.data[4]].Ignore ? 0 : 1; else result = 0;
    if(CanTxMessage.data[5] < ERR_CNT) ErrorList[CanTxMessage.data[5]].Ignore = ErrorList[CanTxMessage.data[5]].Ignore ? 0 : 1; else result = 0;
    if(CanTxMessage.data[6] < ERR_CNT) ErrorList[CanTxMessage.data[6]].Ignore = ErrorList[CanTxMessage.data[6]].Ignore ? 0 : 1; else result = 0;

    if(result == CANIO_ERR_OK) EEP_Write();
    else result = CANIO_ERR_NOTFOUND;

    */
    result = CANIO_ERR_NOTIMPLEMENTED;

    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0xB0_CMD_PWM_CNF(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t PWM_Frq_Selector = 0;
    uint8_t Dither_Frq_Selector = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // PWM_Frq_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // Dither_Frq_Selector

    PWM_Frq_Selector = CanTxMessage.data[1];
    Dither_Frq_Selector = CanTxMessage.data[2];

    /*
    if(PWM_Set_Frq(PWM_Frq_Selector)) result = CANIO_ERR_OUTOFRANGE;
    if(PWM_Set_Dither(Dither_Frq_Selector)) result = CANIO_ERR_OUTOFRANGE;
    */
    result = CANIO_ERR_NOTIMPLEMENTED;

    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0xD0_CMD_TaskHandle(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    uint8_t Selector = 0;
    uint16_t CycleTimer_ms = 0;
    int index = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_NOTIMPLEMENTED;

    return  CanTxMessage;
}

//############################################################# PUBLIC LIB Funktionen #################################################################
int                 LIB_IO_GET_ListSize         (void)
{
    static int savedIndex = 0;
    uint16_t index = 0;
    uint32_t value;

    if(savedIndex) return savedIndex;

    do
    {
        index++;
        value = 0;
        
        value += GenericIOList[index].IO_Type;
        value += GenericIOList[index].HAL_ID;    
        value += GenericIOList[index].isEnabled;
        value += GenericIOList[index].isOutput;
        value += GenericIOList[index].SafeValue;
        value += GenericIOList[index].actualValue;    
        value += GenericIOList[index].actualValue_MIN;
        value += GenericIOList[index].actualValue_MAX;
        value += GenericIOList[index].actualValue_TS;            
    } while ((value != 0) && (index != 0xFFFF));

    if(value == 0xFFFF) savedIndex =  -1;
    else savedIndex =  index;
    return savedIndex;
}


