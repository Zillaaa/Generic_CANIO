
#include "Generic_CANIO\Generic_CANIO.h"
#define CAN_ID_MUX_0XB1_MAGIC       57411
#define CAN_ID_MUX_0XB2_MAGIC       8874
#define CAN_ID_MUX_0X20_MAGIC       56344
tst_CAN_Msg Generic_CAN_clear(void);

//############################################################# Externe Deklarationen #################################################################
extern volatile uint32_t u32OnTimems; // Wird ueber ISR jede ms inkrementiert
extern ten_CanErrorList EEP_Result;
bios_can_msg_typ ConvertTo(tst_CAN_Msg Msg);
tst_CAN_Msg ConvertFrom(bios_can_msg_typ Msg);
uint16_t LIB_current_calc(uint16_t newValue);
ten_CanErrorList writeEEP(void);

//############################################################# IO Handling #################################################################
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
    {IO_OUTPUT_PROM , OUT_HSD0      , 1 , 0 , 0 , 0 , 1000  , 0},   // 8
    {IO_OUTPUT_PROM , OUT_HSD1      , 1 , 0 , 0 , 0 , 1000  , 0},
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

int                 HAL_IO_GET_ListSize         (void)
{
    int index = 0;
    static size_t HAL_IO_GET_ListSize = 0;
    if(HAL_IO_GET_ListSize) return HAL_IO_GET_ListSize;
    
    while(IOList[index].IO_Type != IO_UNKOWN)index++;
    HAL_IO_GET_ListSize = index;
    return HAL_IO_GET_ListSize;
}
uint32_t            HAL_SYS_GET_Millis          (void)
{
    return u32OnTimems;
}
ten_CanErrorList    HAL_IO_GET_Input            (uint8_t index, uint16_t *pReadValue)
{
    ten_CanErrorList result = CAN_ERR_OK;
    uint16_t readValue = 0;
    if(index >= HAL_IO_GET_ListSize()) return CAN_ERR_INDEX_OUTOFRANGE;
    switch(IOList[index].IO_Type)
    {
        default: result = CAN_ERR_UNSUPPORTED; break;
        case IO_INPUT_MV:   readValue = os_algin_mv(IOList[index].HAL_ID); break;
        case IO_INPUT_CURR: readValue = LIB_current_calc(os_algin(IOList[index].HAL_ID)); break;
        case IO_OUTPUT_PROM:
        {
            uint16_t duty = 0;
            switch(IOList[index].HAL_ID)
            {
                default: result = CAN_ERR_UNSUPPORTED; break;
                case OUT_HSD7: duty = os_pwm_duty_read[0].duty; break;
                case OUT_HSD6: duty = os_pwm_duty_read[1].duty; break;
                case OUT_HSD5: duty = os_pwm_duty_read[2].duty; break;
                case OUT_HSD4: duty = os_pwm_duty_read[3].duty; break;
                case OUT_HSD3: duty = os_pwm_duty_read[4].duty; break;
                case OUT_HSD2: duty = os_pwm_duty_read[5].duty; break;                
            }
            if(duty > 1000) duty = 1000; 
            readValue = duty;
        
        }break;
    }

    if(result == CAN_ERR_OK)
    {
        if(readValue > IOList[index].actualValue_MAX) readValue = IOList[index].actualValue_MAX;
        if(readValue < IOList[index].actualValue_MIN) readValue = IOList[index].actualValue_MIN;
        IOList[index].actualValue = readValue;
        IOList[index].actualValue_TS = HAL_SYS_GET_Millis();
        *pReadValue = readValue;
    }

    
    return result;
}
ten_CanErrorList    HAL_IO_SET_Output           (uint8_t index, uint16_t newValue)
{
    ten_CanErrorList result = CAN_ERR_OK;
    if(index >= HAL_IO_GET_ListSize()) return CAN_ERR_INDEX_OUTOFRANGE;
    if(IOList[index].Enabled == 0) 
    {
        newValue = IOList[index].SafeValue;
        result = CAN_ERR_OUTPUT_DISABLED;
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
                default: result = CAN_ERR_UNSUPPORTED; break;
                case OUT_HSD2:  os_pwm_duty_cycle (PWM_IO2, newValue, 500, 0, 0); break;
                case OUT_HSD3:  os_pwm_duty_cycle (PWM_IO3, newValue, 500, 0, 0); break;
                case OUT_HSD4:  os_pwm_duty_cycle (PWM_IO4, newValue, 500, 0, 0); break;
                case OUT_HSD5:  os_pwm_duty_cycle (PWM_IO5, newValue, 500, 0, 0); break;
                case OUT_HSD6:  os_pwm_duty_cycle (PWM_IO6, newValue, 500, 0, 0); break;
                case OUT_HSD7:  os_pwm_duty_cycle (PWM_IO7, newValue, 500, 0, 0); break;
            }
        }break;
        default: result = CAN_ERR_UNSUPPORTED;
    }

    IOList[index].actualValue = newValue;
    IOList[index].actualValue_TS = HAL_SYS_GET_Millis();
    
    
    return result;
}
ten_CanErrorList    HAL_IO_SET_Output_Safe      (uint8_t index, uint16_t newValue)
{
    ten_CanErrorList result = CAN_ERR_OK;
    if(index >= HAL_IO_GET_ListSize()) return CAN_ERR_INDEX_OUTOFRANGE;
    if(IOList[index].actualValue_MIN > newValue) newValue = IOList[index].actualValue_MIN;
    if(IOList[index].actualValue_MAX < newValue) newValue = IOList[index].actualValue_MAX;

    switch(IOList[index].IO_Type)
    {
        case IO_OUTPUT_SW:      
        case IO_OUTPUT_PROM:    
        case IO_OUTPUT_CURR: break;
        default: result = CAN_ERR_UNSUPPORTED; break;
    }
    
    if(result == CAN_ERR_OK)
    {
        IOList[index].SafeValue = newValue;
         
    }
    
    return result;
}
ten_CanErrorList    HAL_IO_SET_Output_Enable    (uint8_t index, uint16_t newValue)
{
    ten_CanErrorList result = CAN_ERR_OK;
    if(index >= HAL_IO_GET_ListSize()) return CAN_ERR_INDEX_OUTOFRANGE;
    switch(IOList[index].IO_Type)
    {
        case IO_OUTPUT_SW:      
        case IO_OUTPUT_PROM:    
        case IO_OUTPUT_CURR: break;
        default: result = CAN_ERR_UNSUPPORTED; break;
    }
    
    if(result == CAN_ERR_OK)
    {
        IOList[index].Enabled = newValue ? 1 : 0;
        if(IOList[index].Enabled == 0)
        {
            result = HAL_IO_SET_Output(index, IOList[index].SafeValue);
        }
                
    }
    
    return result;
}
void                HAL_CAN_SendMsg         (tst_CAN_Msg *Data)
{
   bios_can_msg_typ SendMessage = ConvertTo(*Data);
   (void)bios_can_send_msg(&SendMessage);
}
//############################################################# UserLibs #################################################################
int         LIB_PrintString(tst_CAN_Msg* CanTxMessage, const char* pString)
{
    int i=0;
    static const char* pStringBackup = NULL;
    static uint8_t MUX1 = 0;

    // Haben wir einen neuen String, den wir senden sollen?
    if(pStringBackup != pString)
    {
        pStringBackup = pString;
        MUX1 = 0;
    }

    CanTxMessage->data[1] = MUX1;

    for(i=0; i<5; i++)
    {
        char nextChar = pString[(MUX1 * 5) + i];        
        CanTxMessage->data[2+i] = nextChar;
        if(nextChar == 0) 
        {
            pStringBackup = NULL;
            for(; i<5; i++) CanTxMessage->data[2+i] = 0;
            break;
        }
    }
    MUX1++;

    if(pStringBackup) return 1;
    else return 0;

}
uint16_t    LIB_current_calc(uint16_t newValue)
{
   uint32_t CurrentValue = newValue;
   CurrentValue = 226L * CurrentValue;
   CurrentValue = CurrentValue * 119;
   CurrentValue = CurrentValue / 100; // 1 Digit entspricht 2,26mA
   CurrentValue = CurrentValue / 100; // 1 Digit entspricht 0,8337
   return (uint16_t)CurrentValue;
}


//############################################################# CAN Command List #################################################################
// Bereich System 
extern uint32_t MainLoop_ms;
tst_CAN_Msg CAN_0x00_CMD_PING(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = (uint8_t) (HAL_SYS_GET_Millis() / 1000);
    CanTxMessage.data[2] = CANrxCounter;
    CanTxMessage.data[3] = CANtxCounter;
    CanTxMessage.data[4] = (uint8_t)MainLoop_ms;
    CanTxMessage.data[5] = CANrxOverRun;
    CanTxMessage.data[6] = (uint8_t)EEP_Result;

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x01_SYS_BuildDate(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CAN_ERR_OK;
    while(LIB_PrintString(&CanTxMessage, __DATE__)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x02_SYS_BuildTime(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CAN_ERR_OK;
    while(LIB_PrintString(&CanTxMessage, __TIME__)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x03_SYS_SerNum(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = (uint8_t)(EEPROM_Seriennummer >>  0);
    CanTxMessage.data[2] = (uint8_t)(EEPROM_Seriennummer >>  8);
    CanTxMessage.data[3] = (uint8_t)(EEPROM_Seriennummer >> 16);
    CanTxMessage.data[4] = (uint8_t)(EEPROM_Seriennummer >> 24);
    CanTxMessage.data[5] = 0;
    CanTxMessage.data[7] = CAN_ERR_OK;

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x04_SYS_SWversion(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CAN_ERR_OK;
    while(LIB_PrintString(&CanTxMessage, SYSTEM_VERS)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x05_SYS_BSPversion(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CAN_ERR_UNSUPPORTED;
    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x06_SYS_ProjectName(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CAN_ERR_OK;
    while(LIB_PrintString(&CanTxMessage, SYSTEM_NAME)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x10_INPUT_GET(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CAN_ERR_OK;
    uint8_t IO_Selector = 0;
    uint16_t InputValue = 0;    
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    IO_Selector = CanTxMessage.data[1];
    if(IO_Selector < HAL_IO_GET_ListSize()) CanTxMessage.data[7] = (uint8_t)HAL_IO_GET_Input(IO_Selector, &InputValue);
    else                                    CanTxMessage.data[7] = CAN_ERR_INDEX_NOTFOUND;
    CanTxMessage.data[2] = (uint8_t) (InputValue >> 0);
    CanTxMessage.data[3] = (uint8_t) (InputValue >> 8);
    

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x11_INPUT_ANA0(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[1] = (uint8_t)(os_algin_mv(ANA0) / 100);
    CanTxMessage.data[2] = (uint8_t)(os_algin_mv(ANA1) / 100);
    CanTxMessage.data[3] = (uint8_t)(os_algin_mv(ANA2) / 100);
    CanTxMessage.data[4] = (uint8_t)(os_algin_mv(ANA3) / 100);
    CanTxMessage.data[5] = (uint8_t)(os_algin_mv(ANA4) / 100);
    CanTxMessage.data[6] = (uint8_t)(os_algin_mv(ANA5) / 100);
    CanTxMessage.data[7] = CAN_ERR_OK;
    

    CanTxMessage.data[7] = CAN_ERR_UNSUPPORTED;
    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x12_INPUT_ANA_IO0(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[1] = (uint8_t)(os_algin_mv(ANA_IO0) / 100);
    CanTxMessage.data[2] = (uint8_t)(os_algin_mv(ANA_IO1) / 100);
    CanTxMessage.data[3] = (uint8_t)(os_algin_mv(ANA_IO2) / 100);
    CanTxMessage.data[4] = (uint8_t)(os_algin_mv(ANA_IO3) / 100);
    CanTxMessage.data[5] = (uint8_t)(os_algin_mv(ANA_IO4) / 100);
    CanTxMessage.data[6] = (uint8_t)(os_algin_mv(ANA_IO5) / 100);
    CanTxMessage.data[7] = CAN_ERR_OK;
    

    CanTxMessage.data[7] = CAN_ERR_UNSUPPORTED;
    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x13_INPUT_STAT_ANA_HSD0(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[1] = (uint8_t)(LIB_current_calc(os_algin(STAT_ANA_HSD0)) / 20);
    CanTxMessage.data[2] = (uint8_t)(LIB_current_calc(os_algin(STAT_ANA_HSD1)) / 20);
    CanTxMessage.data[3] = (uint8_t)(LIB_current_calc(os_algin(STAT_ANA_HSD2)) / 20);
    CanTxMessage.data[4] = (uint8_t)(LIB_current_calc(os_algin(STAT_ANA_HSD3)) / 20);
    CanTxMessage.data[5] = (uint8_t)(LIB_current_calc(os_algin(STAT_ANA_HSD4)) / 20);
    CanTxMessage.data[6] = (uint8_t)(LIB_current_calc(os_algin(STAT_ANA_HSD5)) / 20);
    CanTxMessage.data[7] = CAN_ERR_OK;
    

    CanTxMessage.data[7] = CAN_ERR_UNSUPPORTED;
    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x14_INPUT_MISC(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[1] = (uint8_t)(LIB_current_calc(os_algin(STAT_ANA_HSD6)) / 20);
    CanTxMessage.data[2] = (uint8_t)(LIB_current_calc(os_algin(STAT_ANA_HSD7)) / 20);
    CanTxMessage.data[3] = (uint8_t) os_digin(D_IN6);
    CanTxMessage.data[4] = (uint8_t) os_digin(D_IN7);
    CanTxMessage.data[5] = (uint8_t)(os_temperature_read());
    CanTxMessage.data[7] = CAN_ERR_OK;
    

    CanTxMessage.data[7] = CAN_ERR_UNSUPPORTED;
    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x20_OUTPUT_SET(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CAN_ERR_OK;
    uint8_t IO_Selector = 0;
    uint16_t NewValue = 0;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
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
        if(IO_Selector < HAL_IO_GET_ListSize()) CanTxMessage.data[7] = (uint8_t) HAL_IO_SET_Output(IO_Selector, NewValue);
        else                                    CanTxMessage.data[7] = CAN_ERR_INDEX_NOTFOUND;
    } 
    else result = CAN_ERR_MAGICNUMBER_FAIL;
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0x21_OUTPUT_PWM(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    uint16_t duty = 0;
    uint16_t Frq = 0;
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0 
    CanTxMessage.data[1] = (uint8_t)(os_pwm_duty_read[5].duty / 4);
    CanTxMessage.data[2] = (uint8_t)(os_pwm_duty_read[4].duty / 4);
    CanTxMessage.data[3] = (uint8_t)(os_pwm_duty_read[3].duty / 4);
    CanTxMessage.data[4] = (uint8_t)(os_pwm_duty_read[2].duty / 4);
    CanTxMessage.data[5] = (uint8_t)(os_pwm_duty_read[1].duty / 4);
    CanTxMessage.data[6] = (uint8_t)(os_pwm_duty_read[0].duty / 4);
    CanTxMessage.data[7] = CAN_ERR_OK;;
    
    return  CanTxMessage;
}
tst_CAN_Msg CAN_0xA0_CMD_BAUDRATE(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[7] = CAN_ERR_NOTIMPLEMENTED;
    return CanTxMessage;
}
tst_CAN_Msg CAN_0xA1_CMD_SOURCE_ADR(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // New Source Adress

    if((CanRxMessage.data[1] > 0) && (CanRxMessage.data[1] < 0xFF))
    {
        void EEP_update_SourceID(uint8_t newSourceID);
        EEP_update_SourceID(CanRxMessage.data[1]);        
        CanTxMessage.data[7] = (uint8_t) writeEEP();        
    }
    else    CanTxMessage.data[7] = CAN_ERR_OUTOFRANGE;
    return  CanTxMessage;
}
tst_CAN_Msg CAN_0xA2_CMD_TX_CYCLE(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    uint8_t Selector = 0;
    uint16_t CycleTimer_ms = 0;
    int index = 0;
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // Selection
    CanTxMessage.data[2] = CanRxMessage.data[2]; // ms
    CanTxMessage.data[3] = CanRxMessage.data[3]; // ms

    Selector = CanTxMessage.data[1];
    CycleTimer_ms = (uint16_t) (((uint32_t) CanRxMessage.data[2] << 0) + ((uint32_t) CanRxMessage.data[3] << 8));

    index = Generic_CAN_SearchHandler(Selector);

    if(index >= 0)
    {
        if((CycleTimer_ms >= SYSTEM_CAN_TX_CYCLE_MIN) && (CycleTimer_ms <= SYSTEM_CAN_TX_CYCLE_MAX))
        {
            CanHandlerList[index].CycleTimer_ms = CycleTimer_ms;            
            CanTxMessage.data[7] = (uint8_t) writeEEP();
        }
        else CanTxMessage.data[7] = CAN_ERR_OUTOFRANGE;
    }
    else CanTxMessage.data[7] = CAN_ERR_OUTOFRANGE;

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0xA3_CMD_ERR_IGN(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CAN_ERR_OK;
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
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

    if(result == CAN_ERR_OK) writeEEP();
    else result = CAN_ERR_NOTFOUND;

    */
    result = CAN_ERR_NOTIMPLEMENTED;

    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0xB0_CMD_PWM_CNF(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CAN_ERR_OK;
    uint8_t PWM_Frq_Selector = 0;
    uint8_t Dither_Frq_Selector = 0;
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // PWM_Frq_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // Dither_Frq_Selector

    PWM_Frq_Selector = CanTxMessage.data[1];
    Dither_Frq_Selector = CanTxMessage.data[2];

    /*
    if(PWM_Set_Frq(PWM_Frq_Selector)) result = CAN_ERR_OUTOFRANGE;
    if(PWM_Set_Dither(Dither_Frq_Selector)) result = CAN_ERR_OUTOFRANGE;
    */
    result = CAN_ERR_NOTIMPLEMENTED;

    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0xB1_CMD_OUT_SWITCHOFF(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CAN_ERR_OK;
    uint8_t IO_Selector = 0;
    uint8_t NewValue;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    CanTxMessage.data[2] = CanRxMessage.data[2]; // NewValue
    CanTxMessage.data[3] = CanRxMessage.data[3]; // MagicNumber
    CanTxMessage.data[4] = CanRxMessage.data[4]; // MagicNumber

    IO_Selector = CanTxMessage.data[1];
    NewValue    = CanTxMessage.data[2];
    MagicNumber = (uint16_t)(((uint32_t) CanRxMessage.data[3] << 0) + ((uint32_t) CanRxMessage.data[4] << 8));

    if(MagicNumber == CAN_ID_MUX_0XB1_MAGIC)
    {
        if(IO_Selector < HAL_IO_GET_ListSize()) CanTxMessage.data[7] = (uint8_t) HAL_IO_SET_Output_Enable(IO_Selector, NewValue ? 1 : 0);
        else                                    CanTxMessage.data[7] = CAN_ERR_INDEX_NOTFOUND;
    } 
    else result = CAN_ERR_MAGICNUMBER_FAIL;
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CAN_Msg CAN_0xB2_CMD_OUT_SAVESTATE(tst_CAN_Msg CanRxMessage)
{
    tst_CAN_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CAN_ERR_OK;
    uint8_t IO_Selector = 0;
    uint16_t SafeStateValue = 0;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
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

    if(MagicNumber == CAN_ID_MUX_0XB2_MAGIC)
    {
        if(IO_Selector < HAL_IO_GET_ListSize()) CanTxMessage.data[7] = (uint8_t) HAL_IO_SET_Output_Safe(IO_Selector, SafeStateValue);
        else                                    CanTxMessage.data[7] = CAN_ERR_INDEX_NOTFOUND;
    } 
    else result = CAN_ERR_MAGICNUMBER_FAIL;
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}


tst_CAN_Handler_Entry CanHandlerList[] = 
{   
    //MUX0;
    //      CyclicPossible;        
    //      |   CycleTimer_ms; // Wenn nicht null, dann wird der "Handler" mit einer "unvalid" CAN Message gestartet
    //      |   |       CycleTimer_TS;
    //      |   |       |   ExecCounter;
    //      |   |       |   |   CAN_Handler_Function Handler;
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
    { 0x11  , 1 , 200   , 0 , 0 , CAN_0x11_INPUT_ANA0               },
    { 0x12  , 1 , 300   , 0 , 0 , CAN_0x12_INPUT_ANA_IO0            },
    { 0x13  , 1 , 400   , 0 , 0 , CAN_0x13_INPUT_STAT_ANA_HSD0      },
    { 0x14  , 1 , 0     , 0 , 0 , CAN_0x14_INPUT_MISC               },
    // Output                 
    { 0x20  , 0 , 0     , 0 , 0 , CAN_0x20_OUTPUT_SET               },
    { 0x21  , 1 , 1000  , 0 , 0 , CAN_0x21_OUTPUT_PWM               },
    // Allgemeine Steuergeräte Befehle
    { 0xA0  , 0 , 0     , 0 , 0 , CAN_0xA0_CMD_BAUDRATE             },
    { 0xA1  , 0 , 0     , 0 , 0 , CAN_0xA1_CMD_SOURCE_ADR           },
    { 0xA2  , 0 , 0     , 0 , 0 , CAN_0xA2_CMD_TX_CYCLE             },
    { 0xA3  , 0 , 0     , 0 , 0 , CAN_0xA3_CMD_ERR_IGN              },
    // Projekt spezifische Befehle
    { 0xB0  , 0 , 0     , 0 , 0 , CAN_0xB0_CMD_PWM_CNF              },
    { 0xB1  , 0 , 0     , 0 , 0 , CAN_0xB1_CMD_OUT_SWITCHOFF        },
    { 0xB2  , 0 , 0     , 0 , 0 , CAN_0xB2_CMD_OUT_SAVESTATE        },
    { 0xFF  , 0 , 0     , 0 , 0 , NULL                              },  // NICHT VERÄNDERN!!!!
};
