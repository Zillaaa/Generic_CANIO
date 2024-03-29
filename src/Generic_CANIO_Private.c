
#include "Generic_CANIO\include\Generic_CANIO_Private.h"
#include "Generic_CANIO\include\Generic_CANIO_Public.h"

const char hexdig[] = "0123456789ABCDEF";

uint8_t     Generic_CAN_SourceID = CAN_ID_DEFAULT_SA;
uint32_t    Generic_CAN_BusSpeed = CAN_ID_DEFAULT_SPEEED;
uint8_t     Generic_CAN_rxCounter; 
uint8_t     Generic_CAN_txCounter; 
uint8_t     Generic_CAN_rxOverFlow;
uint8_t     Generic_CAN_txOverFlow;
uint8_t     Generic_CAN_cmdCounter;
//############################################################# IB Funktionen #################################################################

void                Generic_CAN_Init                (uint8_t Source_ID)
{
    int i=0;
    Generic_CAN_SourceID    = Source_ID;
    Generic_CAN_BusSpeed    = CAN_ID_DEFAULT_SPEEED;
    Generic_CAN_rxCounter   = 0; 
    Generic_CAN_txCounter   = 0; 
    Generic_CAN_rxOverFlow  = 0;
    Generic_CAN_txOverFlow  = 0;
    Generic_CAN_cmdCounter  = 0;

}
sys_can_msg_t       Generic_CAN_HandleMessage       (sys_can_msg_t ReceivedMessage)
{   
    sys_can_msg_t Message2Send;
    tst_CANIO_Msg CanRxMessage = LIB_CAN_clear(); 
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    int index = 0;
    (void)HAL_ConvertFrom(ReceivedMessage, &CanRxMessage);
    index = LIB_CAN_SearchHandler(CanRxMessage.data[0]);
    Generic_CAN_rxCounter++;
    if(index >= 0)
    {
        Generic_CAN_cmdCounter++;
        CanTxMessage =  CanHandlerList[index].Handler(CanRxMessage);
                        CanHandlerList[index].ExecCounter++;
                        CanHandlerList[index].CycleTimer_TS = HAL_SYS_GET_Millis();    
        if(LIB_CAN_isValid(CanTxMessage))  Generic_CAN_txCounter++; 
    }
    else
    {
        CanTxMessage =  LIB_0xFF_CMD_FEHLER_DEFAULT(CanRxMessage);
    }

    (void)HAL_ConvertTo(CanTxMessage, &Message2Send);

    return Message2Send;
}
void                Generic_CAN_CycliqMessage       (void)
{    
    static size_t index = 0;
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    tst_CANIO_Msg CanRXMessage = LIB_CAN_clear();            
    
    
    if(index >= LIB_CAN_GetSizeOfList()) index = 0;
    
    do
    {
        if(CanHandlerList[index].CyclicPossible)
        {
            if(CanHandlerList[index].CycleTimer_ms)
            {
                if(HAL_SYS_GET_Millis() > CanHandlerList[index].CycleTimer_TS)
                {
                    CanRXMessage.id = 0x18000000 + (CAN_ID_PGN_TX_BC << 8) + Generic_CAN_SourceID;
                    CanRXMessage.data[0] =  CanHandlerList[index].MUX0;
                    CanTxMessage =          CanHandlerList[index].Handler(CanRXMessage);
                                            CanHandlerList[index].ExecCounter++;

                    while(HAL_SYS_GET_Millis() > CanHandlerList[index].CycleTimer_TS)
                    {
                        CanHandlerList[index].CycleTimer_TS += CanHandlerList[index].CycleTimer_ms;
                    }
                    Generic_CAN_txCounter++;
                    if(HAL_CAN_SendMsg(&CanTxMessage)) Generic_CAN_txOverFlow++;
                }
            }
        }
        index++;
    } while (index < LIB_CAN_GetSizeOfList());
       
}

//############################################################# UserLibs: CAN-List #################################################################

uint32_t            LIB_CAN_GetRxCANid              (uint8_t SenderID)
{
    return 0x18000000 + (CAN_ID_PGN_RX_CMD << 8) + ((uint16_t)Generic_CAN_SourceID << 8) + SenderID;
}
size_t              LIB_CAN_GetSizeOfList           (void)
{
    static size_t sizeOfList = 0;
    int i=0;
    if(sizeOfList) return sizeOfList;    
    while(CanHandlerList[i].Handler != NULL) i++;
    sizeOfList = i;
    return sizeOfList;
}
int                 LIB_CAN_SearchHandler           (uint8_t MUX0)
{
    int i=0;
    do
    {
        if(CanHandlerList[i].Handler == NULL) break;
        if(CanHandlerList[i].MUX0 == MUX0)
        {
            return i;
        }    
        i++;    
    }while(1);
    return -1;
}
int                 LIB_CAN_isValid                 (tst_CANIO_Msg CanRXMessage)
{
    if(CanRXMessage.id == 0) return 0;
    if(CanRXMessage.len == 0) return 0;
    return 1;
}
tst_CANIO_Msg       LIB_CAN_clear                   (void)
{
    int i=0;
    tst_CANIO_Msg ClearMessage;
    for(i=0; i<8; i++) ClearMessage.data[i] = 0xFF;
    ClearMessage.id = 0;
    ClearMessage.len = 0;
    return ClearMessage;
}
uint32_t            LIB_CAN_Switch_RXTX             (uint32_t CanId)
{
    uint32_t newCanID = 0;
    if((CanId & 0x00FF0000L) == 0x00EF0000L) 
    {   // Nach J1939 sind nur 0xXXEFXXXX gerichtete Kommunikation, die gedreht werden muss.
        newCanID  =   CanId  & 0xFFFF0000L;
        newCanID +=  ((CanId & 0x000000FFL) << 8);
        newCanID +=  ((CanId & 0x0000FF00L) >> 8);
    }
    else
    {
        newCanID = CanId;
    }
    return newCanID;

}
int                 LIB_CAN_PrintString             (tst_CANIO_Msg* CanTxMessage, const char* pString)
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

    for(i=0; i<6; i++)
    {
        int8_t nextChar = pString[(MUX1 * 6) + i];        
        CanTxMessage->data[7-i] = nextChar;
        // NUll Terminierung erreicht?
        if(nextChar == 0) 
        {
            pStringBackup = NULL;
            for(; i<6; i++) CanTxMessage->data[7-i] = 0;
            break;
        }
    }
    MUX1++;

    if(pStringBackup) return 1;
    else return 0;

}

tst_CANIO_Msg       LIB_0xFF_CMD_FEHLER_DEFAULT     (tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = 0xFF;
    CanTxMessage.data[1] = CanRxMessage.data[0];
    CanTxMessage.data[2] = 0xFF;
    CanTxMessage.data[3] = 0xFF;
    CanTxMessage.data[4] = 0xFF;
    CanTxMessage.data[5] = 0xFF;
    CanTxMessage.data[6] = 0xFF;
    CanTxMessage.data[7] = 0xFF;

    return  CanTxMessage;
}

//############################################################# UserLibs: IO-List #################################################################


ten_CanErrorList    LIB_IO_GET_ListIndex            (ten_IO_Type IO_Type, uint8_t HAL_ID, uint8_t *pIndex )
{
    uint8_t index = 0;
    
    for(index = 0; index < LIB_IO_GET_ListSize(); index++)
    {
        if( (GenericIOList[index].IO_Type == IO_Type) &&
            (GenericIOList[index].HAL_ID == HAL_ID)) 
            {
                *pIndex = index;
                return CANIO_ERR_OK;
            }
    }
    return  CANIO_ERR_INDEX_NOTFOUND;
}
ten_CanErrorList    LIB_IO_SET_Output_Safe          (uint8_t index, ten_IO_Type IO_Type, uint32_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(index >= LIB_IO_GET_ListSize())                  return CANIO_ERR_INDEX_OUTOFRANGE;
    if(GenericIOList[index].isEnabled == 0)             return CANIO_ERR_OUTPUT_DISABLED;
    if(GenericIOList[index].isOutput == 0)              return CANIO_ERR_INDEX_NOT_OUTPUT; 
    if((GenericIOList[index].IO_Type != IO_Type) == 0)  return CANIO_ERR_IOTYPE_DIFFERENT;


    // MIN MAX Pr�fung
     if(GenericIOList[index].actualValue_MIN  > newValue) newValue = GenericIOList[index].actualValue_MIN;
     if(GenericIOList[index].actualValue_MAX < newValue) newValue = GenericIOList[index].actualValue_MAX;

    
    
    
    if(result == CANIO_ERR_OK)
    {
        GenericIOList[index].SafeValue = newValue;         
    }
    
    return result;
}
ten_CanErrorList    LIB_IO_SET_Output_Enable        (uint8_t index, ten_IO_Type IO_Type, uint32_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(index >= LIB_IO_GET_ListSize())          return CANIO_ERR_INDEX_OUTOFRANGE;
    if(GenericIOList[index].isEnabled == 0)     return CANIO_ERR_OUTPUT_DISABLED;
    if(GenericIOList[index].isOutput == 0)      return CANIO_ERR_INDEX_NOT_OUTPUT; 
    if(GenericIOList[index].IO_Type != IO_Type) return CANIO_ERR_IOTYPE_DIFFERENT;

    if(result == CANIO_ERR_OK)
    {
        GenericIOList[index].isEnabled = newValue ? 1 : 0;
        if(GenericIOList[index].isEnabled == 0)
        {
            result = HAL_IO_SET_Output(index, IO_Type, GenericIOList[index].SafeValue);
        }
                
    }
    
    return result;
}

//############################################################# UserLibs: String Handling #################################################################
// Copyright: Atlas GmbH => Detlef Hansen
size_t ASC_vPrintInteger(char *intstr, void *i, ten_ASC_PrintType format)       
{
	uint8_t index;
	uint8_t notzero;
	uint32_t val, divider, digit;
	int32_t  sval;


	notzero = 0;
	index=0;
	if (format == PIT_HEXBYTE  ||  format == PIT_HEXWORD  ||  format == PIT_HEXLONG)
	{
		switch (format)
		{
			case PIT_HEXBYTE:
				val = (uint32_t)(*(uint8_t *)i);
				digit = 2;
				break;

			case PIT_HEXWORD:
				val = (uint32_t)(*(uint16_t *)i);
				digit = 4;
				break;

			case PIT_HEXLONG:
				val = *(uint32_t *)i;
				digit = 8;
				break;
		}

		while (digit)
		{
			digit--;
			intstr[index] = hexdig[(uint16_t)(0xF & (val>>(digit*4)))];
			index++;
		}
	}
	else
	{
		switch (format)
		{
			case PIT_SIGNEDBYTE:
				sval = (int32_t)(*(int8_t *)i);
				divider = 100;
				break;
	
			case PIT_UNSIGNEDBYTE:
				val = (uint32_t)(*(uint8_t *)i);
				divider = 100;
				break;
	
			case PIT_SIGNEDWORD:
				sval = (int32_t)(*(int16_t *)i);
				divider = 10000;
				break;

			case PIT_UNSIGNEDWORD:
				val = (uint32_t)(*(uint16_t *)i);
				divider = 10000;
				break;
	
			case PIT_SIGNEDLONG:
				sval = *(int32_t *)i;
				divider = 1000000000;
				break;
	
			case PIT_UNSIGNEDLONG:
				val = (uint32_t)(*(uint32_t *)i);
				divider = 1000000000;
				break;
		}
		


		if (format == PIT_SIGNEDBYTE || format == PIT_SIGNEDWORD || format == PIT_SIGNEDLONG)
		{
			if (sval < 0)
			{
				val = sval * -1;
				intstr[index++]='-';
			}
			else
			{
				val = sval;
			}
		}

		
        if (val != 0)
        {
            while (divider>0)
            {
                digit = val/divider;
                if (digit > 0)
                {
                    notzero = 1;
                }
                
                if (notzero)
                {
                    intstr[index] = '0'+digit;
                    index++;
                }
                val -= digit*divider;
    
                divider /= 10;
            }
        }
        else
        {
            intstr[index] = '0';
            index++;
        }
		
	}

	intstr[index]='\0';

	return index;
}
//############################################################# UserLibs: Mittelwertbildung #################################################################
uint16_t            LIB_Mittwerlwertbildung         (tst_LaufendeMittelwertBildung_Entry *pData, uint16_t newValue)
{
    int i = 0;
    uint32_t Mittelwertberechnung = 0;
    
    if(newValue)
    {
        if(pData->index >= MITTELWERT_ARITH) pData->index = 0;
        pData->X[pData->index] = newValue;
        pData->index++;   
        pData->TS_last = HAL_SYS_GET_Millis();     
    }
    // Hatten wir �berhaupt jemals werte?
    if(pData->TS_last)
    {    
        // ... bis wir wirklich 0 haben!
        if((HAL_SYS_GET_Millis() - pData->TS_last) > MITTELWERT_TIMEOUT_MS)
        {
            pData->TS_last = 0;
            for(i = 0; i < MITTELWERT_ARITH; i++) pData->X[i] = 0;
        }
        else
        {        
            Mittelwertberechnung = 0;
            for(i = 0; i < MITTELWERT_ARITH; i++) Mittelwertberechnung += pData->X[i];
            Mittelwertberechnung /= MITTELWERT_ARITH;
        }
    }    
    return (uint16_t) Mittelwertberechnung;
}



