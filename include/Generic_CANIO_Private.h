#ifndef GENERIC_CANIO_H
#define GENERIC_CANIO_H


#define CAN_ID_PGN_RX_CMD	        0xEF00L
#define CAN_ID_PGN_TX_BC            0xFFBBL
#define CAN_ID_DEFAULT_SA           0xCC
#define CAN_ID_DEFAULT_SPEEED       250E3

typedef struct CANIO_Message
{
    uint32_t id;
    uint8_t len;
    uint8_t data[8];
}tst_CANIO_Msg;
typedef tst_CANIO_Msg (*CAN_Handler_Function)(tst_CANIO_Msg);
typedef struct CAN_Handler_ListEntry
{
    uint8_t MUX0;
    uint8_t CyclicPossible;        
    uint16_t CycleTimer_ms; // Wenn nicht null, dann wird der "Handler" mit einer "unvalid" CAN Message gestartet
    uint32_t CycleTimer_TS;
    uint16_t ExecCounter;
    CAN_Handler_Function Handler;
}tst_CAN_Handler_Entry;

typedef enum CANIO_ERROR_LIST
{
    CANIO_ERR_OK,
    CANIO_ERR_UNKOWN,
    CANIO_ERR_NOTIMPLEMENTED,
    CANIO_ERR_OUTOFRANGE,
    CANIO_ERR_NOTFOUND,
    CANIO_ERR_MAGICNUMBER_FAIL,
    CANIO_ERR_UNSUPPORTED,
    CANIO_ERR_INDEX_NOTFOUND,
    CANIO_ERR_OUTPUT_DISABLED,
    CANIO_ERR_EEP_PATTERNWRONG,
    CANIO_ERR_EEP_CHECKSUMWRONG,
    CANIO_ERR_INDEX_OUTOFRANGE,
    CANIO_ERR_INDEX_NOT_OUTPUT
}ten_CanErrorList;

typedef enum IO_List_Types
{
    IO_UNKOWN,
    IO_INPUT_MV,
    IO_INPUT_CURR,
    IO_OUTPUT_SW,
    IO_OUTPUT_PROM,
    IO_OUTPUT_CURR
}ten_IO_Type;

typedef struct IOConfigList
{
    ten_IO_Type IO_Type;
    uint8_t HAL_ID;    
    uint8_t Enabled;
    uint32_t SafeValue;
    uint32_t actualValue;    
    uint32_t actualValue_MIN;
    uint32_t actualValue_MAX;
    uint32_t actualValue_TS;    
    
}tst_IO_List_Entry;


extern tst_IO_List_Entry IOList[];
extern tst_CAN_Handler_Entry CanHandlerList[];


//############################################################# PUBLIC PIMARY CALL Funktionen #################################################################
void                Generic_CAN_Init                (uint8_t Source_ID);
tst_CANIO_Msg       Generic_CAN_HandleMessage       (tst_CANIO_Msg CanRxMessage);
void                Generic_CAN_CycliqMessage       (void);


//############################################################# PRIVATE LIB: CAN-List #################################################################

uint32_t            LIB_CAN_GetRxCANid              (uint8_t SenderID);
size_t              LIB_CAN_GetSizeOfList           (void);
int                 LIB_CAN_SearchHandler           (uint8_t MUX0);
tst_CANIO_Msg       LIB_CAN_clear               (void);
int                 LIB_CAN_isValid             (tst_CANIO_Msg CanRXMessage);
uint32_t            LIB_CAN_Switch_RXTX                 (uint32_t CanId);
tst_CANIO_Msg       LIB_0xFF_CMD_FEHLER_DEFAULT     (tst_CANIO_Msg CanRxMessage);


//############################################################# PRIVATE LIB: IO-List #################################################################

int                 LIB_IO_GET_ListSize             (void);
int                 LIB_IO_GET_ListIndex            (uint8_t IO_Type, uint8_t HAL_ID );
ten_CanErrorList    LIB_IO_SET_Output_Safe          (uint8_t index, uint32_t newValue);
ten_CanErrorList    LIB_IO_SET_Output_Enable        (uint8_t index, uint16_t newValue);

//############################################################# PRIVATE LIB: Mittelwertbildung #################################################################
#define MITTELWERT_DELTA_MS_MAX (1000/100)  // PWM MIN = 100Hz
#define MITTELWERT_DELTA_MS_MIN (1000/1000)  // PWM MIN = 1000Hz
#define MITTELWERT_TIMEOUT_MS 1000
#define MITTELWERT_ARITH 10
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