
#include "Generic_CANIO\include\Generic_CANIO_Public.h"
#define CAN_ID_MUX_0X22_MAGIC       57411
#define CAN_ID_MUX_0X21_MAGIC       8874
#define CAN_ID_MUX_0X20_MAGIC       56344
#define SYSTEM_CANIO_TX_CYCLE_MIN 100
#define SYSTEM_CANIO_TX_CYCLE_MAX 60000



uint16_t            HAL_current_calc            (uint16_t newValue);

//############################################################# IO Handling #################################################################
ten_CanErrorList    HAL_IO_GET_Input            (uint8_t index, uint32_t *pReadValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    uint32_t readValue = 0;
    if(index >= LIB_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    switch(IOList[index].IO_Type)
    {
        default: result = CANIO_ERR_UNSUPPORTED; break;
        case IO_INPUT_MV:   readValue = os_algin_mv(IOList[index].HAL_ID); break;
        case IO_INPUT_CURR: readValue = HAL_current_calc(os_algin(IOList[index].HAL_ID)); break;
        case IO_OUTPUT_PROM:
        {
            uint32_t duty = 0;
            switch(IOList[index].HAL_ID)
            {
                default: result = CANIO_ERR_UNSUPPORTED; break;
                case OUT_HSD7: duty = IOList[index].actualValue; break;
                case OUT_HSD6: duty = IOList[index].actualValue; break;
                case OUT_HSD5: duty = IOList[index].actualValue; break;
                case OUT_HSD4: duty = IOList[index].actualValue; break;
                case OUT_HSD3: duty = IOList[index].actualValue; break;
                case OUT_HSD2: duty = IOList[index].actualValue; break;                
            }
            if(duty > 1000) duty = 1000; 
            readValue = duty;
        
        }break;
    }

    if(result == CANIO_ERR_OK)
    {
        if(readValue > IOList[index].actualValue_MAX) readValue = IOList[index].actualValue_MAX;
        if(readValue < IOList[index].actualValue_MIN) readValue = IOList[index].actualValue_MIN;
        IOList[index].actualValue = readValue;
        IOList[index].actualValue_TS = HAL_SYS_GET_Millis();
        *pReadValue = readValue;
    }

    return result;
}
ten_CanErrorList    HAL_IO_SET_Output           (uint8_t index, uint32_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(index >= LIB_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    if( (IOList[index].IO_Type != IO_OUTPUT_CURR) && 
        (IOList[index].IO_Type != IO_OUTPUT_PROM) && 
        (IOList[index].IO_Type != IO_OUTPUT_SW)     ) return CANIO_ERR_INDEX_NOT_OUTPUT; 
    if(IOList[index].Enabled == 0) 
    {
        newValue = IOList[index].SafeValue;
        return CANIO_ERR_OUTPUT_DISABLED;
    }
    if(IOList[index].actualValue_MIN > newValue) newValue = IOList[index].actualValue_MIN;
    if(IOList[index].actualValue_MAX < newValue) newValue = IOList[index].actualValue_MAX;

    switch(IOList[index].IO_Type)
    {
        case IO_OUTPUT_SW:      os_digout(IOList[index].HAL_ID, (uint8_t) newValue); break;
        case IO_OUTPUT_PROM:    
        {
            switch(IOList[index].HAL_ID)
            {
                default: result = CANIO_ERR_UNSUPPORTED; break;
                case OUT_HSD2:  os_pwm_duty_cycle (PWM_IO2, (uint16_t)newValue, 500, 0, 0); break;
                case OUT_HSD3:  os_pwm_duty_cycle (PWM_IO3, (uint16_t)newValue, 500, 0, 0); break;
                case OUT_HSD4:  os_pwm_duty_cycle (PWM_IO4, (uint16_t)newValue, 500, 0, 0); break;
                case OUT_HSD5:  os_pwm_duty_cycle (PWM_IO5, (uint16_t)newValue, 500, 0, 0); break;
                case OUT_HSD6:  os_pwm_duty_cycle (PWM_IO6, (uint16_t)newValue, 500, 0, 0); break;
                case OUT_HSD7:  os_pwm_duty_cycle (PWM_IO7, (uint16_t)newValue, 500, 0, 0); break;
            }
        }break;
        default: result = CANIO_ERR_UNSUPPORTED; break;
    }

    IOList[index].actualValue = newValue;
    IOList[index].actualValue_TS = HAL_SYS_GET_Millis();
    
    
    return result;
}

tst_IO_List_Entry IOList[] = 
{
    //IO_Type;
    //              HAL_ID;    
    //              |               Enabled;        Output Only, Deaktiviert das Ändern des Ausgangszustands
    //              |               |   SafeValue;  Output Only, Wird im Fehlerfall oder beim Start Eingestellt
    //              |               |   |   actualValue;                    Der zuletzt bekannte Zustand
    //              |               |   |   |   actualValue_MIN;            Zustandswert MIN Wert
    //              |               |   |   |   |   actualValue_MAX;                     MAX Wert
    //              |               |   |   |   |   |       actualValue_TS; Zeitpunkt der letzten Zustands-Wert-Änderung
    {IO_OUTPUT_SW   , OUT_HSD0      , 1 , 0 , 0 , 0 , 1     , 0},   // 0
    {IO_OUTPUT_SW   , OUT_HSD1      , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD2      , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD3      , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD4      , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD5      , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD6      , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD7      , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_PROM , OUT_HSD0      , 0 , 0 , 0 , 0 , 1000  , 0},   // 8    // PWM wird an HSD0 und HSD1 nicht unterstützt
    {IO_OUTPUT_PROM , OUT_HSD1      , 0 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD2      , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD3      , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD4      , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD5      , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD6      , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD7      , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_INPUT_MV    , ANA0          , 0 , 0 , 0 , 0 , 34080 , 0},   // 16
    {IO_INPUT_MV    , ANA1          , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA2          , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA3          , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA4          , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA5          , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO0       , 0 , 0 , 0 , 0 , 12000 , 0},   // 22
    {IO_INPUT_MV    , ANA_IO1       , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO2       , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO3       , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO4       , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO5       , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD0 , 0 , 0 , 0 , 0 , 2500  , 0},   // 28
    {IO_INPUT_CURR  , STAT_ANA_HSD1 , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD2 , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD3 , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD4 , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD5 , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD6 , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD7 , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_UNKOWN      , 0             , 0 , 0 , 0 , 0 , 0     , 0}
};

//############################################################# GENERIC CAN Command List #################################################################
// Dies sind die fixierten CMDs, deren Inhalt beibehalten und gefüllt werden müssen.

tst_CANIO_Msg CAN_0x00_CMD_PING(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = (uint8_t) (HAL_SYS_GET_Millis() / 1000);     //CAN_0x00_BC_Runtime
    CanTxMessage.data[2] = CANrxCounter;                                //CAN_0x00_BC_CAN_RX
    CanTxMessage.data[3] = CANtxCounter;                                //CAN_0x00_BC_CAN_TX
    CanTxMessage.data[4] = CANrxOverRun;                                //CAN_0x00_BC_CAN_OF_RX
    CanTxMessage.data[5] = 0;                                           //CAN_0x00_BC_CAN_OF_TX
    CanTxMessage.data[6] = CANcmdCounter;                               //CAN_0x00_BC_CAN_CMD
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
    while(LIB_CAB_PrintString(&CanTxMessage, __DATE__)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x02_SYS_BuildTime(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_CAB_PrintString(&CanTxMessage, __TIME__)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x03_SYS_SerNum(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    char Buffer[10];
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;

    HAL_SYS_Get_SerialNumber(Buffer);

    while(LIB_CAB_PrintString(&CanTxMessage, Buffer)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x04_SYS_SWversion(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_CAB_PrintString(&CanTxMessage, pProjektVersion)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x05_SYS_BSPversion(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_CAB_PrintString(&CanTxMessage, "no BSP Version")) HAL_CAN_SendMsg(&CanTxMessage);

    
    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x06_SYS_ProjectName(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_CAB_PrintString(&CanTxMessage, pProjectName)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x10_INPUT_GET(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    uint32_t InputValue = 0;    
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    IO_Selector = CanTxMessage.data[1];
    if(IO_Selector < LIB_IO_GET_ListSize()) result = (uint8_t)HAL_IO_GET_Input(IO_Selector, &InputValue);
    else                                    result = CANIO_ERR_INDEX_NOTFOUND;
    CanTxMessage.data[2] = (uint8_t) (InputValue >> 0);
    CanTxMessage.data[3] = (uint8_t) (InputValue >> 8);
    CanTxMessage.data[4] = (uint8_t) (InputValue >> 16);
    CanTxMessage.data[5] = (uint8_t) (InputValue >> 24);
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x20_OUTPUT_SET(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    uint16_t NewValue = 0;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // NewValue
    CanTxMessage.data[3] = CanRxMessage.data[3]; // NewValue
    CanTxMessage.data[4] = CanRxMessage.data[4]; // MagicNumber
    CanTxMessage.data[5] = CanRxMessage.data[5]; // MagicNumber

    IO_Selector = CanTxMessage.data[1];
    NewValue = (uint16_t)(((uint32_t) CanRxMessage.data[2] << 0) + ((uint32_t) CanRxMessage.data[3] << 8));
    MagicNumber = (uint16_t)(((uint32_t) CanRxMessage.data[4] << 0) + ((uint32_t) CanRxMessage.data[5] << 8));

    if(MagicNumber == CAN_ID_MUX_0X20_MAGIC)
    {
        if(IO_Selector < LIB_IO_GET_ListSize()) result= (uint8_t) HAL_IO_SET_Output(IO_Selector, NewValue);
        else                                    result = CANIO_ERR_INDEX_NOTFOUND;
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
    uint16_t SafeStateValue = 0;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // SafeState
    CanTxMessage.data[3] = CanRxMessage.data[3]; // SafeState
    CanTxMessage.data[4] = CanRxMessage.data[4]; // MagicNumber
    CanTxMessage.data[5] = CanRxMessage.data[5]; // MagicNumber

    IO_Selector = CanTxMessage.data[1];
    SafeStateValue = (uint16_t)(((uint32_t) CanRxMessage.data[2] << 0) + ((uint32_t) CanRxMessage.data[3] << 8));
    MagicNumber = (uint16_t)(((uint32_t) CanRxMessage.data[4] << 0) + ((uint32_t) CanRxMessage.data[5] << 8));

    if(MagicNumber == CAN_ID_MUX_0X21_MAGIC)
    {
        if(IO_Selector < LIB_IO_GET_ListSize()) CanTxMessage.data[7] = (uint8_t) LIB_IO_SET_Output_Safe(IO_Selector, SafeStateValue);
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
    uint8_t NewValue;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // NewValue
    CanTxMessage.data[3] = CanRxMessage.data[3]; // MagicNumber
    CanTxMessage.data[4] = CanRxMessage.data[4]; // MagicNumber

    IO_Selector = CanTxMessage.data[1];
    NewValue    = CanTxMessage.data[2];
    MagicNumber = (uint16_t)(((uint32_t) CanRxMessage.data[3] << 0) + ((uint32_t) CanRxMessage.data[4] << 8));

    if(MagicNumber == CAN_ID_MUX_0X22_MAGIC)
    {
        if(IO_Selector < LIB_IO_GET_ListSize()) CanTxMessage.data[7] = (uint8_t) LIB_IO_SET_Output_Enable(IO_Selector, NewValue ? 1 : 0);
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
//############################################################# USER CAN Command List #################################################################
// In den Lücken zwischen den "fixierten CMDS" oben, können eigene CAN Nachrichten eingefügt werden.
tst_CANIO_Msg CAN_0x11_INPUT_ANA0(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[1] = (uint8_t)(os_algin_mv(ANA0) / 100);
    CanTxMessage.data[2] = (uint8_t)(os_algin_mv(ANA1) / 100);
    CanTxMessage.data[3] = (uint8_t)(os_algin_mv(ANA2) / 100);
    CanTxMessage.data[4] = (uint8_t)(os_algin_mv(ANA3) / 100);
    CanTxMessage.data[5] = (uint8_t)(os_algin_mv(ANA4) / 100);
    CanTxMessage.data[6] = (uint8_t)(os_algin_mv(ANA5) / 100);
    CanTxMessage.data[7] = CANIO_ERR_OK;
    
    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x12_INPUT_ANA_IO0(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[1] = (uint8_t)(os_algin_mv(ANA_IO0) / 100);
    CanTxMessage.data[2] = (uint8_t)(os_algin_mv(ANA_IO1) / 100);
    CanTxMessage.data[3] = (uint8_t)(os_algin_mv(ANA_IO2) / 100);
    CanTxMessage.data[4] = (uint8_t)(os_algin_mv(ANA_IO3) / 100);
    CanTxMessage.data[5] = (uint8_t)(os_algin_mv(ANA_IO4) / 100);
    CanTxMessage.data[6] = (uint8_t)(os_algin_mv(ANA_IO5) / 100);
    CanTxMessage.data[7] = CANIO_ERR_OK;
    
    return  CanTxMessage;
}
tst_LaufendeMittelwertBildung_Entry Mittelwert[5] = {0};
tst_CANIO_Msg CAN_0x13_INPUT_STAT_ANA_HSD0(tst_CANIO_Msg CanRxMessage)
{
    
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    
    CanTxMessage.data[1] = (uint8_t)(HAL_current_calc(LIB_Mittwerlwertbildung(&Mittelwert[0] ,os_algin(STAT_ANA_HSD0))) / 10);
    CanTxMessage.data[2] = (uint8_t)(HAL_current_calc(LIB_Mittwerlwertbildung(&Mittelwert[1] ,os_algin(STAT_ANA_HSD1))) / 10);
    CanTxMessage.data[3] = (uint8_t)(HAL_current_calc(LIB_Mittwerlwertbildung(&Mittelwert[2] ,os_algin(STAT_ANA_HSD2))) / 10);
    CanTxMessage.data[4] = (uint8_t)(HAL_current_calc(LIB_Mittwerlwertbildung(&Mittelwert[3] ,os_algin(STAT_ANA_HSD3))) / 10);
    CanTxMessage.data[5] = (uint8_t)(HAL_current_calc(LIB_Mittwerlwertbildung(&Mittelwert[4] ,os_algin(STAT_ANA_HSD4))) / 10);
    CanTxMessage.data[6] = (uint8_t)(HAL_current_calc(LIB_Mittwerlwertbildung(&Mittelwert[5] ,os_algin(STAT_ANA_HSD5))) / 10);
    CanTxMessage.data[7] = CANIO_ERR_OK;
    

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x14_INPUT_MISC(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[1] = (uint8_t)(HAL_current_calc(os_algin(STAT_ANA_HSD6)) / 10);
    CanTxMessage.data[2] = (uint8_t)(HAL_current_calc(os_algin(STAT_ANA_HSD7)) / 10);
    CanTxMessage.data[3] = (uint8_t) os_digin(D_IN6);
    CanTxMessage.data[4] = (uint8_t) os_digin(D_IN7);
    CanTxMessage.data[5] = (uint8_t)(os_temperature_read());
    CanTxMessage.data[7] = CANIO_ERR_OK;
    

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x23_OUTPUT_PWM(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    uint16_t duty = 0;
    uint16_t Frq = 0;
    int index = 0;
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0 
    index = LIB_IO_GET_ListIndex(IO_OUTPUT_PROM, OUT_HSD2); CanTxMessage.data[1] = (uint8_t) ((index >= 0) ? (IOList[index].actualValue/4) : 0xFF);
    index = LIB_IO_GET_ListIndex(IO_OUTPUT_PROM, OUT_HSD2); CanTxMessage.data[2] = (uint8_t) ((index >= 0) ? (IOList[index].actualValue/4) : 0xFF);
    index = LIB_IO_GET_ListIndex(IO_OUTPUT_PROM, OUT_HSD3); CanTxMessage.data[3] = (uint8_t) ((index >= 0) ? (IOList[index].actualValue/4) : 0xFF);
    index = LIB_IO_GET_ListIndex(IO_OUTPUT_PROM, OUT_HSD4); CanTxMessage.data[4] = (uint8_t) ((index >= 0) ? (IOList[index].actualValue/4) : 0xFF);
    index = LIB_IO_GET_ListIndex(IO_OUTPUT_PROM, OUT_HSD5); CanTxMessage.data[5] = (uint8_t) ((index >= 0) ? (IOList[index].actualValue/4) : 0xFF);
    index = LIB_IO_GET_ListIndex(IO_OUTPUT_PROM, OUT_HSD6); CanTxMessage.data[6] = (uint8_t) ((index >= 0) ? (IOList[index].actualValue/4) : 0xFF);
    CanTxMessage.data[7] = 0;
    CanTxMessage.data[7] |= (os_digin(D_IN0) ? 1 : 0) << 0;
    CanTxMessage.data[7] |= (os_digin(D_IN1) ? 1 : 0) << 1;
    
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
tst_CANIO_Msg CAN_0xD1_CMD_TaskHandle(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    uint8_t Selector = 0;
    uint16_t CycleTimer_ms = 0;
    int index = 0;
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;

    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = (uint8_t) (uint8_t) (MainLoop_ms >> 0);
    CanTxMessage.data[2] = (uint8_t) (uint8_t) (MainLoop_ms >> 8);
    CanTxMessage.data[3] = (uint8_t) (uint8_t) (MainLoop_len_ms >> 0);
    CanTxMessage.data[4] = (uint8_t) (uint8_t) (MainLoop_len_ms >> 8);
    CanTxMessage.data[7] = CANIO_ERR_OK;

    return  CanTxMessage;
}    

tst_CAN_Handler_Entry CanHandlerList[] = 
{   
    //MUX0;
    //        Enable Cycle: wird mit dem Public ID (0x18FFBB<SA>)         gesendet.
    //        |   CycleTimer_ms; // Wenn nicht null, dann wird der "Handler" mit einer "unvalid" CAN Message gestartet
    //        |   |       CycleTimer_TS, Zeitpunkt des letzten Versands
    //        |   |       |   ExecCounter; wie oft wurde dieser Befehl ausgeführt.
    //        |   |       |   |   CAN_Handler_Function Handler;
    { 0x00  , 1 , 100   , 0 , 0 , CAN_0x00_CMD_PING                 },
    // System  Befehle    
    { 0x01  , 0 , 0     , 0 , 0 , CAN_0x01_SYS_BuildDate            },
    { 0x02  , 0 , 0     , 0 , 0 , CAN_0x02_SYS_BuildTime            },
    { 0x03  , 0 , 0     , 0 , 0 , CAN_0x03_SYS_SerNum               },
    { 0x04  , 0 , 0     , 0 , 0 , CAN_0x04_SYS_SWversion            },
    { 0x05  , 0 , 0     , 0 , 0 , CAN_0x05_SYS_BSPversion           },
    { 0x06  , 0 , 0     , 0 , 0 , CAN_0x06_SYS_ProjectName          },
    // Input              
    { 0x10  , 0 , 200   , 0 , 0 , CAN_0x10_INPUT_GET                },
    { 0x11  , 1 , 500   , 0 , 0 , CAN_0x11_INPUT_ANA0               },
    { 0x12  , 1 , 500   , 0 , 0 , CAN_0x12_INPUT_ANA_IO0            },
    { 0x13  , 1 , 500   , 0 , 0 , CAN_0x13_INPUT_STAT_ANA_HSD0      },
    { 0x14  , 1 , 500   , 0 , 0 , CAN_0x14_INPUT_MISC               },
    // Output                 
    { 0x20  , 0 , 0     , 0 , 0 , CAN_0x20_OUTPUT_SET               },
    { 0x21  , 0 , 0     , 0 , 0 , CAN_0x21_OUTPUT_SAVESTATE         },
    { 0x22  , 0 , 0     , 0 , 0 , CAN_0x22_OUTPUT_SWITCHOFF         },
    { 0x23  , 0 , 1000  , 0 , 0 , CAN_0x23_OUTPUT_PWM               },
    // Allgemeine Steuergeräte Befehle
    { 0xA0  , 0 , 0     , 0 , 0 , CAN_0xA0_CMD_BAUDRATE             },
    { 0xA1  , 0 , 0     , 0 , 0 , CAN_0xA1_CMD_SOURCE_ADR           },
    { 0xA2  , 0 , 0     , 0 , 0 , CAN_0xA2_CMD_TX_CYCLE             },
    { 0xA3  , 0 , 0     , 0 , 0 , CAN_0xA3_CMD_ERR_IGN              },
    // Projekt spezifische Befehle
    { 0xB0  , 0 , 0     , 0 , 0 , CAN_0xB0_CMD_PWM_CNF              },
    // Task Management
    { 0xD0  , 0 , 0     , 0 , 0 , CAN_0xD0_CMD_TaskHandle           },
    { 0xD1  , 1 , 100   , 0 , 0 , CAN_0xD1_CMD_TaskHandle           },
    { 0xFF  , 0 , 0     , 0 , 0 , NULL                              },  // NICHT VERÄNDERN!!!!
};
//################# WENN die Source-Datei nicht autoamtisch compiliert werden kann #################
#include "Generic_CANIO\src\Generic_CANIO_Private.c"