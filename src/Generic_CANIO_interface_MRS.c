
#include "Generic_CANIO\include\Generic_CANIO_interface_MRS.h"
#include "Generic_CANIO\include\Generic_CANIO_Public.h"
#include "Generic_CANIO\include\Generic_CANIO_Private.h"

const char* pProjectName = SYSTEM_NAME;
const char* pProjektVersion = SYSTEM_VERS;

#define MINIMUM(a,b) ((a > b)? b : a)
#define MAXIMUM(a,b) ((a > b)? a : b)

tst_IO_List_Entry GenericIOList[] = {
    //IO_Type;
    //              HAL_ID;    
    //              |                           Enabled;        Output Only, Deaktiviert das Ändern des Ausgangszustands
    //              |                           |   isOutput
    //              |                           |   |   SafeValue;  Output Only, Wird im Fehlerfall oder beim Start Eingestellt
    //              |                           |   |   |   actualValue;                    Der zuletzt bekannte Zustand
    //              |                           |   |   |   |   actualValue_MIN;            Zustandswert MIN Wert
    //              |                           |   |   |   |   |   actualValue_MAX;                     MAX Wert
    //              |                           |   |   |   |   |   |       actualValue_TS; Zeitpunkt der letzten Zustands-Wert-Änderung
    //              |                           |   |   |   |   |   |       |   pCustomData
//  ##################################### Analoge Eingänge #####################################
    {IO_OUTPUT_SW   , OUT_HSD0                  , 1 , 1 , 0 , 0 , 0 , 1     , 0, NULL},   // 0
    {IO_OUTPUT_SW   , OUT_HSD1                  , 1 , 1 , 0 , 0 , 0 , 1     , 0, NULL},
    {IO_OUTPUT_SW   , OUT_HSD2                  , 1 , 1 , 0 , 0 , 0 , 1     , 0, NULL},
    {IO_OUTPUT_SW   , OUT_HSD3                  , 1 , 1 , 0 , 0 , 0 , 1     , 0, NULL},
    {IO_OUTPUT_SW   , OUT_HSD4                  , 1 , 1 , 0 , 0 , 0 , 1     , 0, NULL},
    {IO_OUTPUT_SW   , OUT_HSD5                  , 1 , 1 , 0 , 0 , 0 , 1     , 0, NULL},
    {IO_OUTPUT_SW   , OUT_HSD6                  , 1 , 1 , 0 , 0 , 0 , 1     , 0, NULL},
    {IO_OUTPUT_SW   , OUT_HSD7                  , 1 , 1 , 0 , 0 , 0 , 1     , 0, NULL},
    {IO_OUTPUT_PROM , OUT_HSD2                  , 1 , 1 , 0 , 0 , 0 , 1000  , 0, NULL},   // 8
    {IO_OUTPUT_PROM , OUT_HSD3                  , 1 , 1 , 0 , 0 , 0 , 1000  , 0, NULL},
    {IO_OUTPUT_PROM , OUT_HSD4                  , 1 , 1 , 0 , 0 , 0 , 1000  , 0, NULL},
    {IO_OUTPUT_PROM , OUT_HSD5                  , 1 , 1 , 0 , 0 , 0 , 1000  , 0, NULL},
    {IO_OUTPUT_PROM , OUT_HSD6                  , 1 , 1 , 0 , 0 , 0 , 1000  , 0, NULL},
    {IO_OUTPUT_PROM , OUT_HSD7                  , 1 , 1 , 0 , 0 , 0 , 1000  , 0, NULL},
    {IO_INPUT_MV    , ANA0                      , 0 , 0 , 0 , 0 , 0 , 34080 , 0, NULL},   // 14
    {IO_INPUT_MV    , ANA1                      , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_MV    , ANA2                      , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_MV    , ANA3                      , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_MV    , ANA4                      , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_MV    , ANA5                      , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_MV    , ANA_IO0                   , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},   // 20
    {IO_INPUT_MV    , ANA_IO1                   , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_MV    , ANA_IO2                   , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_MV    , ANA_IO3                   , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_MV    , ANA_IO4                   , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_MV    , ANA_IO5                   , 0 , 0 , 0 , 0 , 0 , 12000 , 0, NULL},
    {IO_INPUT_CURR  , STAT_ANA_HSD0             , 0 , 0 , 0 , 0 , 0 , 2500  , 0, NULL},   // 26
    {IO_INPUT_CURR  , STAT_ANA_HSD1             , 0 , 0 , 0 , 0 , 0 , 2500  , 0, NULL},
    {IO_INPUT_CURR  , STAT_ANA_HSD2             , 0 , 0 , 0 , 0 , 0 , 2500  , 0, NULL},
    {IO_INPUT_CURR  , STAT_ANA_HSD3             , 0 , 0 , 0 , 0 , 0 , 2500  , 0, NULL},
    {IO_INPUT_CURR  , STAT_ANA_HSD4             , 0 , 0 , 0 , 0 , 0 , 2500  , 0, NULL},
    {IO_INPUT_CURR  , STAT_ANA_HSD5             , 0 , 0 , 0 , 0 , 0 , 2500  , 0, NULL},
    {IO_INPUT_CURR  , STAT_ANA_HSD6             , 0 , 0 , 0 , 0 , 0 , 2500  , 0, NULL},
    {IO_INPUT_CURR  , STAT_ANA_HSD7             , 0 , 0 , 0 , 0 , 0 , 2500  , 0, NULL},
    {IO_UNKOWN      , 0                         , 0 , 0 , 0 , 0 , 0 , 0     , 0, NULL}
};
const size_t GenericIOList_sizeof = (sizeof(GenericIOList) / sizeof(tst_IO_List_Entry)) + 1;


//############################################################# PUBLIC HAL Funktionen #################################################################
// Alle Hardware Abstraktion Handler müssen umgesetzt werden, damit die Library funktioniert!
ten_CanErrorList __common_ReadValue(uint8_t IOIndex, uint32_t *pValue);
ten_CanErrorList __common_WriteValue(uint8_t IOIndex, uint32_t newValue);
uint16_t            __common_current_calc            (uint16_t newValue);

ten_CanErrorList    HAL_IO_GET_Input_mV         (uint8_t IOIndex, uint32_t *pValue)
{
    return __common_ReadValue(IOIndex, pValue);
}
ten_CanErrorList    HAL_IO_GET_Input_mA         (uint8_t IOIndex, uint32_t *pValue)
{
	return __common_ReadValue(IOIndex, pValue);
}
ten_CanErrorList    HAL_IO_GET_Output_ppm       (uint8_t IOIndex, uint32_t *pValue)
{
	return __common_ReadValue(IOIndex, pValue);
}
ten_CanErrorList    HAL_IO_GET_Output_bool      (uint8_t IOIndex, uint32_t *pValue)
{
	return __common_ReadValue(IOIndex, pValue);
}
ten_CanErrorList    HAL_IO_GET_Output_mA        (uint8_t IOIndex, uint32_t *pValue)
{
	return __common_ReadValue(IOIndex, pValue);
}
ten_CanErrorList    HAL_IO_SET_Output_ppm       (uint8_t IOIndex, uint32_t newValue)
{
	return __common_WriteValue(IOIndex, newValue);
}
ten_CanErrorList    HAL_IO_SET_Output_bool      (uint8_t IOIndex, uint32_t newValue)
{
	return __common_WriteValue(IOIndex, newValue);
}
ten_CanErrorList    HAL_IO_SET_Output_mA        (uint8_t IOIndex, uint32_t newValue)
{
	return __common_WriteValue(IOIndex, newValue);
}
ten_CanErrorList    HAL_CAN_SendMsg             (tst_CANIO_Msg *Msg2Send)
{
    bios_can_msg_typ SendMessage = {0};
    ten_CanErrorList result = HAL_ConvertTo(*Msg2Send, &SendMessage);
    if(result == CANIO_ERR_OK)
    {
        CANtxCounter++;
        (void)bios_can_send_msg(&SendMessage);
    }
    return result;
}
ten_CanErrorList    HAL_update_SourceID         (uint8_t newSourceID)
{
    void EEP_update_SourceID(uint8_t newSourceID);
    EEP_update_SourceID(newSourceID);
    return CANIO_ERR_OK;
}
uint32_t            HAL_SYS_GET_Millis          (void)
{
	return u32OnTimems;
}
void                HAL_SYS_Get_SerialNumber    (char* pBuffer, size_t sizeOfBuffer)
{
    size_t pos = 0;
    unsigned long Seriennummer; 
    (void)IEE1_GetData(EEPROM_Adresse_Seriennummer,(byte*)&Seriennummer,EEPROM_LEN_Seriennummer);	
    
    pos += ASC_vPrintInteger(&pBuffer[pos], &Seriennummer, PIT_HEXLONG);
	
}
void                HAL_SYS_Get_ProjektVersion  (uint8_t* pBuffer, size_t sizeOfBuffer)
{
    int i=0;
    for(i=0; i< MINIMUM(sizeOfBuffer, strlen(pProjektVersion)); i++)
    {
        pBuffer[i] = pProjektVersion[i];
    }   
}
void                HAL_SYS_Get_pProjectName    (char* pBuffer, size_t sizeOfBuffer)
{
    int i=0;
    for(i=0; i< MINIMUM(sizeOfBuffer, strlen(pProjectName) + 1) - 1; i++)
    {
        pBuffer[i] = pProjectName[i];
    }    
    pBuffer[i] = 0;
}
void                HAL_SYS_Get_pBSPversion     (uint8_t* pBuffer, size_t sizeOfBuffer)
{
    pBuffer[0] = 0;
    //NOT AVAILABLE  
}
ten_CanErrorList    HAL_WRITE_EEP               (void)
{
	ten_CanErrorList EEP_Write(void);
    return EEP_Write();
}
ten_CanErrorList    HAL_ConvertTo               (tst_CANIO_Msg Msg, sys_can_msg_t* newMessage)
{
    newMessage->data[0]  = Msg.data[0];
    newMessage->data[1]  = Msg.data[1];
    newMessage->data[2]  = Msg.data[2];
    newMessage->data[3]  = Msg.data[3];
    newMessage->data[4]  = Msg.data[4];
    newMessage->data[5]  = Msg.data[5];
    newMessage->data[6]  = Msg.data[6];
    newMessage->data[7]  = Msg.data[7];
    newMessage->id       = Msg.id;
    newMessage->id_ext   = 1;
    newMessage->len      = Msg.len;
    newMessage->prty     = 0;
    newMessage->remote_tx = 0;
   return CANIO_ERR_OK;
}
ten_CanErrorList    HAL_ConvertFrom             (sys_can_msg_t Msg, tst_CANIO_Msg* newMessage)
{
    newMessage->data[0]  = Msg.data[0];
    newMessage->data[1]  = Msg.data[1];
    newMessage->data[2]  = Msg.data[2];
    newMessage->data[3]  = Msg.data[3];
    newMessage->data[4]  = Msg.data[4];
    newMessage->data[5]  = Msg.data[5];
    newMessage->data[6]  = Msg.data[6];
    newMessage->data[7]  = Msg.data[7];
    newMessage->id       = Msg.id;
    newMessage->len      = Msg.len;
	return CANIO_ERR_OK;
}


//############################################################# USER CAN Command List #################################################################
// In den Lücken zwischen den "fixierten CMDS" , können eigene CAN Nachrichten eingefügt werden.

tst_CANIO_Msg CAN_0x11_INPUT_Generic(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;    
    uint32_t InputValue = 0;    
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    IO_Selector = CanRxMessage.data[0] - 0x11;

    if(HAL_IO_GET_Input((IO_Selector * 7) + 14 + 0, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[1] = (uint8_t) (InputValue / 100L);
    if(HAL_IO_GET_Input((IO_Selector * 7) + 14 + 1, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[2] = (uint8_t) (InputValue / 100L);
    if(HAL_IO_GET_Input((IO_Selector * 7) + 14 + 2, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[3] = (uint8_t) (InputValue / 100L);
    if(HAL_IO_GET_Input((IO_Selector * 7) + 14 + 3, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[4] = (uint8_t) (InputValue / 100L);
    if(HAL_IO_GET_Input((IO_Selector * 7) + 14 + 4, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[5] = (uint8_t) (InputValue / 100L);
    if(HAL_IO_GET_Input((IO_Selector * 7) + 14 + 5, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[6] = (uint8_t) (InputValue / 100L);
    if(HAL_IO_GET_Input((IO_Selector * 7) + 14 + 6, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[7] = (uint8_t) (InputValue / 100L);
    
    return  CanTxMessage;
}   
tst_LaufendeMittelwertBildung_Entry HSD[8] = {0};
tst_CANIO_Msg CAN_0x30_OUTPUT_CURR(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;    
    uint32_t InputValue = 0;    
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    
    if(HAL_IO_GET_Input(26 + 0, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[1] = (uint8_t) (LIB_Mittwerlwertbildung(&HSD[0], (uint16_t)InputValue) / 100L);
    if(HAL_IO_GET_Input(26 + 1, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[2] = (uint8_t) (LIB_Mittwerlwertbildung(&HSD[1], (uint16_t)InputValue) / 100L);
    if(HAL_IO_GET_Input(26 + 2, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[3] = (uint8_t) (LIB_Mittwerlwertbildung(&HSD[2], (uint16_t)InputValue) / 100L);
    if(HAL_IO_GET_Input(26 + 3, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[4] = (uint8_t) (LIB_Mittwerlwertbildung(&HSD[3], (uint16_t)InputValue) / 100L);
    if(HAL_IO_GET_Input(26 + 4, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[5] = (uint8_t) (LIB_Mittwerlwertbildung(&HSD[4], (uint16_t)InputValue) / 100L);
    if(HAL_IO_GET_Input(26 + 5, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[6] = (uint8_t) (LIB_Mittwerlwertbildung(&HSD[5], (uint16_t)InputValue) / 100L);
    if(HAL_IO_GET_Input(26 + 6, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[7] = (uint8_t) (LIB_Mittwerlwertbildung(&HSD[6], (uint16_t)InputValue) / 100L);
    
    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x31_OUTPUT_CURR(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;    
    uint32_t InputValue = 0;    
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    if(HAL_IO_GET_Input(26 + 7, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[1] = (uint8_t) (LIB_Mittwerlwertbildung(&HSD[7], (uint16_t)InputValue) / 100L);
    
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
    { 0x11  , 1 , 100   , 0 , 0 , CAN_0x11_INPUT_Generic            },
    { 0x12  , 1 , 100   , 0 , 0 , CAN_0x11_INPUT_Generic            },
    // Output                 
    { 0x20  , 0 , 0     , 0 , 0 , CAN_0x20_OUTPUT_SET               },
    { 0x21  , 0 , 0     , 0 , 0 , CAN_0x21_OUTPUT_SAVESTATE         },
    { 0x22  , 0 , 0     , 0 , 0 , CAN_0x22_OUTPUT_SWITCHOFF         },
    // Output CURR                 
    { 0x30  , 1 , 100   , 0 , 0 , CAN_0x30_OUTPUT_CURR               },
    { 0x31  , 1 , 100   , 0 , 0 , CAN_0x31_OUTPUT_CURR               },
    // Allgemeine Steuergeräte Befehle
    { 0xA0  , 0 , 0     , 0 , 0 , CAN_0xA0_CMD_BAUDRATE             },
    { 0xA1  , 0 , 0     , 0 , 0 , CAN_0xA1_CMD_SOURCE_ADR           },
    { 0xA2  , 0 , 0     , 0 , 0 , CAN_0xA2_CMD_TX_CYCLE             },
    { 0xA3  , 0 , 0     , 0 , 0 , CAN_0xA3_CMD_ERR_IGN              },
    // Projekt spezifische Befehle
    { 0xB0  , 0 , 0     , 0 , 0 , CAN_0xB0_CMD_PWM_CNF              },
    // Task Management
    { 0xD0  , 0 , 0     , 0 , 0 , CAN_0xD0_CMD_TaskHandle           },
    { 0xFF  , 0 , 0     , 0 , 0 , NULL                              },  // NICHT VERÄNDERN!!!!
};


//############################################################# Common Libs #################################################################
ten_CanErrorList __common_ReadValue(uint8_t IOIndex, uint32_t *pValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    uint32_t readValue = 0;
    if(IOIndex >= LIB_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    switch(GenericIOList[IOIndex].IO_Type)
    {
        default: result = CANIO_ERR_UNSUPPORTED; break;
        case IO_INPUT_MV:   readValue = os_algin_mv(GenericIOList[IOIndex].HAL_ID); break;
        case IO_INPUT_CURR: readValue = __common_current_calc(os_algin(GenericIOList[IOIndex].HAL_ID)); break;
        case IO_OUTPUT_PROM:
        {
            uint16_t duty = 0;
            switch(GenericIOList[IOIndex].HAL_ID)
            {
                default: result = CANIO_ERR_UNSUPPORTED; break;
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

    if(result == CANIO_ERR_OK)
    {
        if(readValue > GenericIOList[IOIndex].actualValue_MAX) readValue = GenericIOList[IOIndex].actualValue_MAX;
        if(readValue < GenericIOList[IOIndex].actualValue_MIN) readValue = GenericIOList[IOIndex].actualValue_MIN;
        GenericIOList[IOIndex].actualValue = readValue;
        GenericIOList[IOIndex].actualValue_TS = HAL_SYS_GET_Millis();
        *pValue = readValue;
    }

    
    return result;
}
ten_CanErrorList __common_WriteValue(uint8_t IOIndex, uint32_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(IOIndex >= LIB_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    if(GenericIOList[IOIndex].isEnabled == 0) 
    {
        newValue = GenericIOList[IOIndex].SafeValue;
        result = CANIO_ERR_OUTPUT_DISABLED;
    }
    if(GenericIOList[IOIndex].actualValue_MIN > newValue) newValue = GenericIOList[IOIndex].actualValue_MIN;
    if(GenericIOList[IOIndex].actualValue_MAX < newValue) newValue = GenericIOList[IOIndex].actualValue_MAX;

    switch(GenericIOList[IOIndex].IO_Type)
    {
        case IO_OUTPUT_SW:      os_digout(GenericIOList[IOIndex].HAL_ID, (uint8_t) newValue); break;
        case IO_OUTPUT_PROM:    
        {
            switch(GenericIOList[IOIndex].HAL_ID)
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
        default: result = CANIO_ERR_UNSUPPORTED;
    }

    GenericIOList[IOIndex].actualValue = newValue;
    GenericIOList[IOIndex].actualValue_TS = HAL_SYS_GET_Millis();
    
    
    return result;
}   
uint16_t            __common_current_calc            (uint16_t newValue)
{
    uint32_t CurrentValue = newValue;
    CurrentValue = 226L * CurrentValue;
    CurrentValue = CurrentValue * 119;
    CurrentValue = CurrentValue / 100; // 1 Digit entspricht 2,26mA
    CurrentValue = CurrentValue / 100; // 1 Digit entspricht 0,8337
    return (uint16_t)CurrentValue;
}


