
#include "Generic_CANIO\include\Generic_CANIO_Private.h"

uint8_t     Generic_CAN_SourceID = CAN_ID_DEFAULT_SA;
uint32_t    Generic_CAN_BusSpeed = CAN_ID_DEFAULT_SPEEED;

//############################################################# IB Funktionen #################################################################

void                Generic_CAN_Init                (uint8_t Source_ID)
{
    Generic_CAN_SourceID = Source_ID;
}
tst_CANIO_Msg       Generic_CAN_HandleMessage       (tst_CANIO_Msg CanRxMessage)
{    
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    int index = LIB_CAN_SearchHandler(CanRxMessage.data[0]);

    if(index >= 0)
    {
        CanTxMessage =  CanHandlerList[index].Handler(CanRxMessage);
                        CanHandlerList[index].ExecCounter++;
                        CanHandlerList[index].CycleTimer_TS = HAL_SYS_GET_Millis();                
    }
    else
    {
        CanTxMessage =  LIB_0xFF_CMD_FEHLER_DEFAULT(CanRxMessage);
    }

    return CanTxMessage;
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
                    HAL_CAN_SendMsg(&CanTxMessage);
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
    uint32_t newCanID = 0 + ((uint32_t)CAN_ID_PGN_RX_CMD << 8);
    if((CanId & 0x00FF0000) == newCanID) 
    {   // Nach J1939 sind nur 0xXXEFXXXX gerichtete Kommunikation, die gedreht werden muss.
        newCanID  =   CanId  & 0xFFFF0000;
        newCanID +=  ((CanId & 0x000000FF) << 8);
        newCanID +=  ((CanId & 0x0000FF00) >> 8);
    }
    else
    {
        newCanID = CanId;
    }
    return newCanID;

}
int                 LIB_CAB_PrintString             (tst_CANIO_Msg* CanTxMessage, const char* pString)
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

int                 LIB_IO_GET_ListSize             (void)
{
    int index = 0;
    static size_t LIB_IO_GET_ListSize = 0;
    if(LIB_IO_GET_ListSize) return LIB_IO_GET_ListSize;
    
    while(IOList[index].IO_Type != IO_UNKOWN)index++;
    LIB_IO_GET_ListSize = index;
    return LIB_IO_GET_ListSize;
}
int                 LIB_IO_GET_ListIndex            (uint8_t IO_Type, uint8_t HAL_ID )
{
    int index = 0;
    
    for(index = 0; index < LIB_IO_GET_ListSize(); index++)
    {
        if( (IOList[index].IO_Type == IO_Type) &&
            (IOList[index].HAL_ID == HAL_ID)) return index;
    }
    return  -1;
}
ten_CanErrorList    LIB_IO_SET_Output_Safe          (uint8_t index, uint32_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(index >= LIB_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    if(IOList[index].actualValue_MIN > newValue) newValue = IOList[index].actualValue_MIN;
    if(IOList[index].actualValue_MAX < newValue) newValue = IOList[index].actualValue_MAX;

    switch(IOList[index].IO_Type)
    {
        case IO_OUTPUT_SW:      
        case IO_OUTPUT_PROM:    
        case IO_OUTPUT_CURR: break;
        default: result = CANIO_ERR_UNSUPPORTED; break;
    }
    
    if(result == CANIO_ERR_OK)
    {
        IOList[index].SafeValue = newValue;
         
    }
    
    return result;
}
ten_CanErrorList    LIB_IO_SET_Output_Enable        (uint8_t index, uint16_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(index >= LIB_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    switch(IOList[index].IO_Type)
    {
        case IO_OUTPUT_SW:      
        case IO_OUTPUT_PROM:    
        case IO_OUTPUT_CURR: break;
        default: result = CANIO_ERR_UNSUPPORTED; break;
    }
    
    if(result == CANIO_ERR_OK)
    {
        IOList[index].Enabled = newValue ? 1 : 0;
        if(IOList[index].Enabled == 0)
        {
            result = HAL_IO_SET_Output(index, IOList[index].SafeValue);
        }
                
    }
    
    return result;
}

//############################################################# UserLibs: Mittelwertbildung #################################################################

uint16_t            LIB_Mittwerlwertbildung         (tst_LaufendeMittelwertBildung_Entry *pData, uint16_t newValue)
{
    uint16_t delta_ms = 0;
    uint32_t Mittelwertberechnung = 0;
    // Die 0en müssen aussortiert werden...
    if(newValue)
    {
        if(pData->index > MITTELWERT_ARITH) pData->index = 0;
        pData->X[pData->index] = newValue;
        pData->index++;   
        pData->TS_last = HAL_SYS_GET_Millis();     
    }
    else
    {
        // ... bis wir wirklich 0 haben!
        if((HAL_SYS_GET_Millis() - pData->TS_last) > MITTELWERT_TIMEOUT_MS)
        {
            for(delta_ms = 0; delta_ms < MITTELWERT_ARITH; delta_ms++) pData->X[delta_ms] = 0;
        }
    }

    Mittelwertberechnung = 0;
    for(delta_ms = 0; delta_ms < MITTELWERT_ARITH; delta_ms++) Mittelwertberechnung += pData->X[delta_ms];
    Mittelwertberechnung /= MITTELWERT_ARITH;

    return (uint16_t) Mittelwertberechnung;
}



