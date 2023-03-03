
#include "Generic_CANIO.h"
#define CAN_ID_MUX_0XB1_MAGIC       57411
#define CAN_ID_MUX_0XB2_MAGIC       8874
#define CAN_ID_MUX_0X20_MAGIC       56344
#define SYSTEM_CAN_TX_CYCLE_MIN 100
#define SYSTEM_CAN_TX_CYCLE_MAX 60000
tst_CANIO_Msg Generic_CAN_clear(void);

//############################################################# Externe Deklarationen #################################################################
typedef struct CAN_Message
{
    unsigned long id;
    unsigned char data[8];
    unsigned char extended;
    unsigned char dlc;
    
    // http://www.microcontrol-blog.net/2013/03/finger-weg-von-can-remote-frames/
    // Außer CANopen erlaubt kein mir bekanntes Higher-Layer Protokoll (HLP) die Verwendung von Remote Frames, in der SAE J1939 oder in DeviceNet ist die Verwendung sogar explizit verboten. Und dies hat einen guten Grund: Remote Frames führen in der Praxis zu erheblichen Problemen, die ich im folgenden beschreiben möchte.
    unsigned char rtr;

}tst_CAN_Msg;


extern const char *Projekt_Name;
extern const char *Projekt_Vers;

int                 HAL_OutputCurrGetmA(uint8_t index, float* pCurrent_mA);
int                 HAL_OutputCurrSetmA(uint8_t index, float* pCurrent_mA);
char*               HAL_SYS_Get_SerialNumber(void);
int                 HAL_WRITE_EEP(void);
void                HAL_CAN_SendMsg         (tst_CANIO_Msg *Data); // main.cpp
void                HAL_update_SourceID(uint8_t newSourceID);
void                HAL_CMD_PING_Data(uint8_t *pData);
//############################################################# IO Handling #################################################################
tst_IO_List_Entry IOList[] = 
{
    //IO_Type;
    //              HAL_ID;    
    //              |               Enabled;        Output Only, Deaktiviert das �ndern des Ausgangszustands
    //              |               |   SafeValue;  Output Only, Wird im Fehlerfall oder beim Start Eingestellt
    //              |               |   |   actualValue;                    Der zuletzt bekannte Zustand
    //              |               |   |   |   actualValue_MIN;            Zustandswert MIN Wert
    //              |               |   |   |   |   actualValue_MAX;                     MAX Wert
    //              |               |   |   |   |   |       actualValue_TS; Zeitpunkt der letzten Zustands-Wert-�nderung
   
    {IO_INPUT_CURR  ,  0 , 0 , 0 , 0 , 0 , 30000  , 0},   // 0
    {IO_INPUT_CURR  ,  1 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  ,  2 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  ,  3 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  ,  4 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  ,  5 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  ,  6 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  ,  7 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  ,  8 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  ,  9 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  , 10 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  , 11 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  , 12 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  , 13 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  , 14 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_INPUT_CURR  , 15 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR ,  0 , 0 , 0 , 0 , 0 , 30000  , 0},   // 16
    {IO_OUTPUT_CURR ,  1 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR ,  2 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR ,  3 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR ,  4 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR ,  5 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR ,  6 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR ,  7 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR ,  8 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR ,  9 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR , 10 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR , 11 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR , 12 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR , 13 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR , 14 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_OUTPUT_CURR , 15 , 0 , 0 , 0 , 0 , 30000  , 0},
    {IO_UNKOWN      , 0             , 0 , 0 , 0 , 0 , 0     , 0}
};


tst_CAN_Msg         HAL_ConvertTo(tst_CANIO_Msg Msg)
{
    tst_CAN_Msg newMessage;
    for(int i=0; i<8; i++) newMessage.data[i] = Msg.data[i];
    newMessage.id = Msg.id;
    newMessage.dlc = Msg.len;
    newMessage.extended = 1;
    newMessage.rtr = 0;
    return newMessage;
}
tst_CANIO_Msg       HAL_ConvertFrom(tst_CAN_Msg Msg)
{
    tst_CANIO_Msg newMessage;
    for(int i=0; i<8; i++) newMessage.data[i] = Msg.data[i];
    newMessage.id = Msg.id;
    newMessage.len = Msg.dlc;
    return newMessage;
}
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
    return millis();
}

ten_CanErrorList    HAL_IO_GET_Input            (uint8_t index, uint32_t *pReadValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    uint16_t readValue = 0;
    if(index >= HAL_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    switch(IOList[index].IO_Type)
    {
        default: result = CANIO_ERR_UNSUPPORTED; break;
        case IO_INPUT_CURR: 
        {
            float resultmA = 0;
            result = HAL_OutputCurrGetmA(IOList[index].HAL_ID, &resultmA); 
            readValue = (uint16_t) (resultmA * 10);            
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
ten_CanErrorList    HAL_IO_SET_Output           (uint8_t index, uint16_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(index >= HAL_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    if(IOList[index].Enabled == 0) 
    {
        newValue = IOList[index].SafeValue;
        result = CANIO_ERR_OUTPUT_DISABLED;
    }
    if(IOList[index].actualValue_MIN > newValue) newValue = IOList[index].actualValue_MIN;
    if(IOList[index].actualValue_MAX < newValue) newValue = IOList[index].actualValue_MAX;

    switch(IOList[index].IO_Type)
    {
        case IO_OUTPUT_CURR:      
        {
            float newfValue = newValue / 1000.0;
            result = HAL_OutputCurrSetmA(IOList[index].HAL_ID, &newfValue);
            newValue = (uint16_t) (newfValue * 1000);
        }break;
        default: result = CANIO_ERR_UNSUPPORTED;
    }

    IOList[index].actualValue = newValue;
    IOList[index].actualValue_TS = HAL_SYS_GET_Millis();
    
    
    return result;
}
ten_CanErrorList    HAL_IO_SET_Output_Safe      (uint8_t index, uint16_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(index >= HAL_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
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
ten_CanErrorList    HAL_IO_SET_Output_Enable    (uint8_t index, uint16_t newValue)
{
    ten_CanErrorList result = CANIO_ERR_OK;
    if(index >= HAL_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
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

//############################################################# UserLibs #################################################################
int         LIB_PrintString(tst_CANIO_Msg* CanTxMessage, const char* pString)
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

//############################################################# CAN Command List #################################################################
// Bereich System 

tst_CANIO_Msg CAN_0x00_CMD_PING(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = (uint8_t) (HAL_SYS_GET_Millis() / 1000);
    HAL_CMD_PING_Data(CanTxMessage.data);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x01_SYS_BuildDate(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_PrintString(&CanTxMessage, __DATE__)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x02_SYS_BuildTime(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_PrintString(&CanTxMessage, __TIME__)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x03_SYS_SerNum(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;

    while(LIB_PrintString(&CanTxMessage, HAL_SYS_Get_SerialNumber())) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x04_SYS_SWversion(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_PrintString(&CanTxMessage, Projekt_Vers)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x05_SYS_BSPversion(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_PrintString(&CanTxMessage, esp_get_idf_version())) HAL_CAN_SendMsg(&CanTxMessage);

    
    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x06_SYS_ProjectName(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[7] = CANIO_ERR_OK;
    while(LIB_PrintString(&CanTxMessage, Projekt_Name)) HAL_CAN_SendMsg(&CanTxMessage);

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x10_INPUT_GET(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    uint32_t InputValue = 0;    
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    CanTxMessage.data[1] = CanRxMessage.data[1]; // IO_Selector
    IO_Selector = CanTxMessage.data[1];
    if(IO_Selector < HAL_IO_GET_ListSize()) CanTxMessage.data[7] = (uint8_t)HAL_IO_GET_Input(IO_Selector, &InputValue);
    else                                    CanTxMessage.data[7] = CANIO_ERR_INDEX_NOTFOUND;
    CanTxMessage.data[2] = (uint8_t) (InputValue >> 0);
    CanTxMessage.data[3] = (uint8_t) (InputValue >> 8);
    

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x20_OUTPUT_SET(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
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
        else                                    CanTxMessage.data[7] = CANIO_ERR_INDEX_NOTFOUND;
    } 
    else result = CANIO_ERR_MAGICNUMBER_FAIL;
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x21_OUTPUT_STATUS(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    uint32_t NewValue = 0;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    if(HAL_IO_GET_Input(0, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[1] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(1, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[2] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(2, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[3] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(3, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[4] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(4, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[5] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(5, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[6] = (uint8_t) NewValue;    
    CanTxMessage.data[7] = CANIO_ERR_OK;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x22_OUTPUT_STATUS(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    uint32_t NewValue = 0;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    if(HAL_IO_GET_Input( 6, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[1] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input( 7, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[2] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input( 8, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[3] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input( 9, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[4] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(10, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[5] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(11, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[6] = (uint8_t) NewValue;    
    CanTxMessage.data[7] = CANIO_ERR_OK;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x23_OUTPUT_STATUS(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
    uint8_t IO_Selector = 0;
    uint32_t NewValue = 0;
    uint16_t MagicNumber = 0;
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    if(HAL_IO_GET_Input(12, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[1] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(13, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[2] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(14, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[3] = (uint8_t) NewValue;
    if(HAL_IO_GET_Input(15, &NewValue) == CANIO_ERR_OK) CanTxMessage.data[4] = (uint8_t) NewValue;
    CanTxMessage.data[7] = CANIO_ERR_OK;

    return  CanTxMessage;
}
tst_CANIO_Msg CAN_0x2F_OUTPUT_SAVESTATE(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    ten_CanErrorList result = CANIO_ERR_OK;
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
        else                                    CanTxMessage.data[7] = CANIO_ERR_INDEX_NOTFOUND;
    } 
    else result = CANIO_ERR_MAGICNUMBER_FAIL;
    CanTxMessage.data[7] = (uint8_t) result;

    return  CanTxMessage;
}

tst_CANIO_Msg CAN_0xA0_CMD_BAUDRATE(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0

    CanTxMessage.data[7] = CANIO_ERR_NOTIMPLEMENTED;
    return CanTxMessage;
}
tst_CANIO_Msg CAN_0xA1_CMD_SOURCE_ADR(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
    
    CanTxMessage.id = Generic_CAN_Switch_RXTX(CanRxMessage.id);
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
    tst_CANIO_Msg CanTxMessage = Generic_CAN_clear();
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
            CanTxMessage.data[7] = (uint8_t) HAL_WRITE_EEP();
        }
        else CanTxMessage.data[7] = CANIO_ERR_OUTOFRANGE;
    }
    else CanTxMessage.data[7] = CANIO_ERR_OUTOFRANGE;

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
    // Output                 
    { 0x20  , 0 , 0     , 0 , 0 , CAN_0x20_OUTPUT_SET               },
    { 0x21  , 1 , 1000  , 0 , 0 , CAN_0x21_OUTPUT_STATUS            },
    { 0x22  , 1 , 1000  , 0 , 0 , CAN_0x22_OUTPUT_STATUS            },
    { 0x23  , 1 , 1000  , 0 , 0 , CAN_0x23_OUTPUT_STATUS            },
    { 0x2F  , 0 , 0     , 0 , 0 , CAN_0x2F_OUTPUT_SAVESTATE         },
    // Allgemeine Steuerger�te Befehle
    { 0xA0  , 0 , 0     , 0 , 0 , CAN_0xA0_CMD_BAUDRATE             },
    { 0xA1  , 0 , 0     , 0 , 0 , CAN_0xA1_CMD_SOURCE_ADR           },
    { 0xA2  , 0 , 0     , 0 , 0 , CAN_0xA2_CMD_TX_CYCLE             },
   // Projekt spezifische Befehle
    
    { 0xFF  , 0 , 0     , 0 , 0 , NULL                              },  // NICHT VER�NDERN!!!!
};
