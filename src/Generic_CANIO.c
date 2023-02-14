
#include "Generic_CANIO.h"
#define CAN_ID_PGN_RX_CMD	        0xEF00L
#define CAN_ID_PGN_TX_BC            0xFFBBL
#define CAN_ID_DEFAULT_SA           0xCC
#define CAN_ID_DEFAULT_SPEEED       250E3
uint8_t     Generic_CAN_SourceID = CAN_ID_DEFAULT_SA;
uint32_t    Generic_CAN_BusSpeed = CAN_ID_DEFAULT_SPEEED;


//############################################################# Externe Deklarationen #################################################################
void                HAL_CAN_SendMsg(tst_CANIO_Msg *Data);

//############################################################# IB Funktionen #################################################################

uint32_t    Generic_CAN_Switch_RXTX     (uint32_t CanId)
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
int         Generic_CAN_isValid         (tst_CANIO_Msg CanRXMessage)
{
    if(CanRXMessage.id == 0) return 0;
    if(CanRXMessage.len == 0) return 0;
    return 1;
}
tst_CANIO_Msg Generic_CAN_clear           (void)
{
    int i=0;
    tst_CANIO_Msg ClearMessage;
    for(i=0; i<8; i++) ClearMessage.data[i] = 0xFF;
    ClearMessage.id = 0;
    ClearMessage.len = 0;
    return ClearMessage;
}

tst_CANIO_Msg CAN_0xFF_CMD_FEHLER(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
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

//############################################################# SYSTEM Funktionen #################################################################

void        Generic_CAN_Init(uint8_t Source_ID)
{
    Generic_CAN_SourceID = Source_ID;
}
uint32_t    Generic_CAN_GetRxCANid(void)
{
    return 0x18000000 + CAN_ID_PGN_RX_CMD << 8 + Generic_CAN_SourceID;
}
size_t      Generic_CAN_GetSizeOfList(void)
{
    static size_t sizeOfList = 0;
    int i=0;
    if(sizeOfList) return sizeOfList;    
    while(CanHandlerList[i].Handler != NULL) i++;
    sizeOfList = i;
    return sizeOfList;
}
int         Generic_CAN_SearchHandler(uint8_t MUX0)
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
tst_CANIO_Msg Generic_CAN_HandleMessage(tst_CANIO_Msg CanRxMessage)
{    
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    int index = Generic_CAN_SearchHandler(CanRxMessage.data[0]);

    if(index >= 0)
    {
        CanTxMessage =  CanHandlerList[index].Handler(CanRxMessage);
                        CanHandlerList[index].ExecCounter++;
                        CanHandlerList[index].CycleTimer_TS = HAL_SYS_GET_Millis();                
    }
    else
    {
        CanTxMessage =  CAN_0xFF_CMD_FEHLER(CanRxMessage);
    }

    return CanTxMessage;
}
void        Generic_CAN_CycliqMessage(void)
{    
    static size_t index = 0;
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    tst_CANIO_Msg CanRXMessage = Generic_CAN_clear();            
    
    
    if(index >= Generic_CAN_GetSizeOfList()) index = 0;
    
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
    } while (index < Generic_CAN_GetSizeOfList());
       
}


//################# WENN die Source-Datei nicht autoamtisch compiliert werden kann #################
#include "Generic_CANIO_user.c"
