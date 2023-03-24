
#include "Generic_CANIO_interface_MRS.h"
#include "Generic_CANIO_Public.h"
#include "Generic_CANIO_Private.h"


#define MINIMUM(a,b) ((a > b)? b : a)
#define MAXIMUM(a,b) ((a > b)? a : b)

const tst_IO_List_Entry GenericIOList_DEFAULT[] =
{
    //IO_Type;
    //              HAL_ID;    
    //              |                           Enabled;        Output Only, Deaktiviert das Ändern des Ausgangszustands
    //              |                           |   SafeValue;  Output Only, Wird im Fehlerfall oder beim Start Eingestellt
    //              |                           |   |   actualValue;                    Der zuletzt bekannte Zustand
    //              |                           |   |   |   actualValue_MIN;            Zustandswert MIN Wert
    //              |                           |   |   |   |   actualValue_MAX;                     MAX Wert
    //              |                           |   |   |   |   |       actualValue_TS; Zeitpunkt der letzten Zustands-Wert-Änderung
//  ##################################### Analoge Eingänge #####################################
    {IO_OUTPUT_SW   , OUT_HSD0                  , 1 , 0 , 0 , 0 , 1     , 0},   // 0
    {IO_OUTPUT_SW   , OUT_HSD1                  , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD2                  , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD3                  , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD4                  , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD5                  , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD6                  , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_SW   , OUT_HSD7                  , 1 , 0 , 0 , 0 , 1     , 0},
    {IO_OUTPUT_PROM , OUT_HSD0                  , 1 , 0 , 0 , 0 , 1000  , 0},   // 8
    {IO_OUTPUT_PROM , OUT_HSD1                  , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD2                  , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD3                  , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD4                  , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD5                  , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD6                  , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_OUTPUT_PROM , OUT_HSD7                  , 1 , 0 , 0 , 0 , 1000  , 0},
    {IO_INPUT_MV    , ANA0                      , 0 , 0 , 0 , 0 , 34080 , 0},   // 16
    {IO_INPUT_MV    , ANA1                      , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA2                      , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA3                      , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA4                      , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA5                      , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO0                   , 0 , 0 , 0 , 0 , 12000 , 0},   // 22
    {IO_INPUT_MV    , ANA_IO1                   , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO2                   , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO3                   , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO4                   , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_MV    , ANA_IO5                   , 0 , 0 , 0 , 0 , 12000 , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD0             , 0 , 0 , 0 , 0 , 2500  , 0},   // 28
    {IO_INPUT_CURR  , STAT_ANA_HSD1             , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD2             , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD3             , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD4             , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD5             , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD6             , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_INPUT_CURR  , STAT_ANA_HSD7             , 0 , 0 , 0 , 0 , 2500  , 0},
    {IO_UNKOWN      , 0                         , 0 , 0 , 0 , 0 , 0     , 0}
};
const size_t GenericIOList_sizeof = (sizeof(GenericIOList_DEFAULT) / sizeof(tst_IO_List_Entry)) + 1;
tst_IO_List_Entry GenericIOList[GenericIOList_sizeof];

//############################################################# PUBLIC HAL Funktionen #################################################################
// Alle Hardware Abstraktion Handler müssen umgesetzt werden, damit die Library funktioniert!
ten_CanErrorList __common_ReadValue(uint8_t IOIndex, uint32_t *pValue, ten_IO_ParamListe ParameterTypeSelecotr);
ten_CanErrorList __common_WriteValue(uint8_t IOIndex, uint32_t newValue, ten_IO_ParamListe ParameterTypeSelecotr);

ten_CanErrorList    HAL_IO_GET_Input_mV         (uint8_t IOIndex, uint32_t *pValue)
{
    return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_IO_GET_Input_mA         (uint8_t IOIndex, uint32_t *pValue)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_IO_GET_Output_ppm       (uint8_t IOIndex, uint32_t *pValue)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_IO_GET_Output_bool      (uint8_t IOIndex, uint32_t *pValue)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_IO_GET_Output_mA        (uint8_t IOIndex, uint32_t *pValue)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_IO_SET_Output_ppm       (uint8_t IOIndex, uint32_t newValue)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_IO_SET_Output_bool      (uint8_t IOIndex, uint32_t newValue)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_IO_SET_Output_mA        (uint8_t IOIndex, uint32_t newValue)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_CAN_SendMsg             (tst_CANIO_Msg *Msg2Send)
{
    sys_can_msg_t SendMessage = ConvertTo(*Msg2Send);
   (void)bios_can_send_msg(&SendMessage);
   return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_update_SourceID         (uint8_t newSourceID)
{
    return CANIO_ERR_NOTIMPLEMENTED;
}
uint32_t            HAL_SYS_GET_Millis          (void)
{
	return u32OnTimems;
}
void                HAL_SYS_Get_SerialNumber    (char* pBuffer, size_t sizeOfBuffer)
{
    int i=0;
    for(i=0; i< MINIMUM(sizeOfBuffer, Du16WInfo_eECUHWSerialNumberSize); i++)
    {
        pBuffer[i] = DstWInfo_eFactoryData.tu8ECUHWSerialNumber_Str[i];
    }
}
void                HAL_SYS_Get_ProjektVersion  (uint8_t* pBuffer, size_t sizeOfBuffer)
{
    size_t pos = 0;
	
    pos += ASC_vPrintInteger(&pBuffer[pos], &CstApp_eSWIdent.u8V0, PIT_UNSIGNEDBYTE);
	pBuffer[pos] = '.'; pos++;
    pos += ASC_vPrintInteger(&pBuffer[pos], &CstApp_eSWIdent.u8V1, PIT_UNSIGNEDBYTE);
	pBuffer[pos] = '.'; pos++;
    pos += ASC_vPrintInteger(&pBuffer[pos], &CstApp_eSWIdent.u8V2, PIT_UNSIGNEDBYTE);
	pBuffer[pos] = '.'; pos++;
    pos += ASC_vPrintInteger(&pBuffer[pos], &CstApp_eSWIdent.u8V3, PIT_UNSIGNEDBYTE);
}
void                HAL_SYS_Get_pProjectName    (char* pBuffer, size_t sizeOfBuffer)
{
    int i=0;
    for(i=0; i< MINIMUM(sizeOfBuffer, Du16WVersion_eVNameSize); i++)
    {
        pBuffer[i] = CstApp_eSWIdent.tu8VName[i];
    }    
}
void                HAL_SYS_Get_pBSPversion     (uint8_t* pBuffer, size_t sizeOfBuffer)
{
    size_t pos = 0;
	
    pos += ASC_vPrintInteger(&pBuffer[pos], &CstApp_eSWIdent.u8V0, PIT_UNSIGNEDBYTE);
	pBuffer[pos] = '.'; pos++;
    pos += ASC_vPrintInteger(&pBuffer[pos], &CstApp_eSWIdent.u8V1, PIT_UNSIGNEDBYTE);
	pBuffer[pos] = '.'; pos++;
    pos += ASC_vPrintInteger(&pBuffer[pos], &CstApp_eSWIdent.u8V2, PIT_UNSIGNEDBYTE);
	pBuffer[pos] = '.'; pos++;
    pos += ASC_vPrintInteger(&pBuffer[pos], &CstApp_eSWIdent.u8V3, PIT_UNSIGNEDBYTE);   
}
ten_CanErrorList    HAL_WRITE_EEP               (void)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_ConvertTo               (tst_CANIO_Msg Msg, sys_can_msg_t* pDest)
{
   return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_ConvertFrom             (sys_can_msg_t Msg, tst_CANIO_Msg* pDest)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}


//############################################################# USER CAN Command List #################################################################
// In den Lücken zwischen den "fixierten CMDS" , können eigene CAN Nachrichten eingefügt werden.


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
    // Output                 
    { 0x20  , 0 , 0     , 0 , 0 , CAN_0x20_OUTPUT_SET               },
    { 0x21  , 0 , 0     , 0 , 0 , CAN_0x21_OUTPUT_SAVESTATE         },
    { 0x22  , 0 , 0     , 0 , 0 , CAN_0x22_OUTPUT_SWITCHOFF         },
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
ten_CanErrorList __common_ReadValue(uint8_t IOIndex, uint32_t *pValue, ten_IO_ParamListe ParameterTypeSelecotr)
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
ten_CanErrorList __common_WriteValue(uint8_t IOIndex, uint32_t newValue, ten_IO_ParamListe ParameterTypeSelecotr)
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


