
#include "Generic_CANIO_interface.h"
#include "Generic_CANIO_Public.h"
#include "Generic_CANIO_Private.h"

// INCLUDE USER LIBS HERE ONLY:


#define MINIMUM(a,b) ((a > b)? b : a)
#define MAXIMUM(a,b) ((a > b)? a : b)

const tst_IO_List_Entry GenericIOList_DEFAULT[] =
{
//	IO_Type		    HAL_ID	                    isEnabled		actualValue				actualValue_TS
//	|			    |		                    |	isOutput	|		actualValue_MAX	|		pCustomData
//	|			    |		                    |	|	SafeValue		|		actualValue_MIN	|

//  ##################################### Analoge Eingänge #####################################
    {IO_INPUT_MV    , Ceu16WIO_eUN01			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_CURR    , Ceu16WIO_eUN02			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_OUTPUT_SW    , Ceu16WIO_eUN03			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_OUTPUT_CURR    , Ceu16WIO_eUN04			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_OUTPUT_PROM    , Ceu16WIO_eUN05			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_UNKOWN	, 0		, 0 , 0	, 0		, 0		, 0		, 0		, 0		, 0		}	// NIEMALS VERAENDERN!!!!
};
const size_t GenericIOList_sizeof = (sizeof(GenericIOList_DEFAULT) / sizeof(tst_IO_List_Entry)) + 1;
tst_IO_List_Entry GenericIOList[GenericIOList_sizeof];

//############################################################# PUBLIC HAL Funktionen #################################################################
// Alle Hardware Abstraktion Handler müssen umgesetzt werden, damit die Library funktioniert!

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
   return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_update_SourceID         (uint8_t newSourceID)
{
    return CANIO_ERR_NOTIMPLEMENTED;
}
uint32_t            HAL_SYS_GET_Millis          (void)
{
	return 0;
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
ten_CanErrorList    HAL_ConvertTo               (tst_CANIO_Msg Msg, TstWJ1939_eTPLMsgData* pDest)
{
   return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_ConvertFrom             (TstWJ1939_eTPLMsgData Msg, tst_CANIO_Msg* pDest)
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


