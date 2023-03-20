#ifndef GENERIC_CANIO_PRIVATE_H
#define GENERIC_CANIO_PRIVATE_H
#include "Generic_CANIO_interface.h"


#define CAN_ID_PGN_RX_CMD	        0xEF00L
#define CAN_ID_PGN_TX_BC            0xFFBBL
#define CAN_ID_DEFAULT_SA           0xCC
#define CAN_ID_DEFAULT_SPEEED       250E3


extern uint8_t     Generic_CAN_rxCounter; 
extern uint8_t     Generic_CAN_txCounter; 
extern uint8_t     Generic_CAN_rxOverFlow;
extern uint8_t     Generic_CAN_txOverFlow;
extern uint8_t     Generic_CAN_cmdCounter;




//############################################################# PRIVATE LIB: CAN-List #################################################################

uint32_t            LIB_CAN_GetRxCANid              (uint8_t SenderID);
size_t              LIB_CAN_GetSizeOfList           (void);
int                 LIB_CAN_SearchHandler           (uint8_t MUX0);
tst_CANIO_Msg       LIB_CAN_clear                   (void);
int                 LIB_CAN_isValid                 (tst_CANIO_Msg CanRXMessage);
uint32_t            LIB_CAN_Switch_RXTX             (uint32_t CanId);
tst_CANIO_Msg       LIB_0xFF_CMD_FEHLER_DEFAULT     (tst_CANIO_Msg CanRxMessage);


//############################################################# PRIVATE LIB: IO-List #################################################################

ten_CanErrorList    LIB_IO_GET_ListIndex            (ten_IO_Type IO_Type, uint8_t HAL_ID, uint8_t *pIndex );
ten_CanErrorList    LIB_IO_SET_Output_Safe          (uint8_t index, ten_IO_Type IO_Type, uint32_t newValue);
ten_CanErrorList    LIB_IO_SET_Output_Enable        (uint8_t index, ten_IO_Type IO_Type, uint32_t newValue);

//############################################################# PRIVATE LIB: Mittelwertbildung #################################################################
#define MITTELWERT_DELTA_MS_MAX (1000/100)  // PWM MIN = 100Hz
#define MITTELWERT_DELTA_MS_MIN (1000/1000)  // PWM MIN = 1000Hz
#define MITTELWERT_TIMEOUT_MS 1000
#define MITTELWERT_ARITH 7
typedef struct Mittelwertbildung
{
    uint8_t index;
    uint16_t X[MITTELWERT_ARITH];
    uint32_t TS_last;
    
}tst_LaufendeMittelwertBildung_Entry;
uint16_t            LIB_Mittwerlwertbildung         (tst_LaufendeMittelwertBildung_Entry *pData, uint16_t newValue);

//############################################################# PRIVATE LIB: MISC #################################################################
int                 LIB_CAB_PrintString                 (tst_CANIO_Msg* CanTxMessage, const char* pString);



#endif