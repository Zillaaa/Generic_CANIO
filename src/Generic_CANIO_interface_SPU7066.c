
#include "Generic_CANIO_interface_SPU7066.h"
#include "Generic_CANIO_Public.h"
#include "Generic_CANIO_Private.h"
#include "version.h"
#include "IO_Handling.h"
#include "util.h"

#define MINIMUM(a,b) ((a > b)? b : a)
#define MAXIMUM(a,b) ((a > b)? a : b)


tst_IO_List_Entry GenericIOList[] =
{
//	IO_Type		    HAL_ID	                    isEnabled		actualValue				actualValue_TS
//	|			    |		                    |	isOutput	|		actualValue_MAX	|		pCustomData
//	|			    |		                    |	|	SafeValue		|		actualValue_MIN	|

//  ##################################### Analoge Eingänge #####################################
    {IO_INPUT_MV    , Ceu16WIO_eUN01			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN02			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN03			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN04			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN05			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN06			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN07			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN08			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN09			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN10			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN11			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN12			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN13			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN14			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN15			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN16			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN17			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN18			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN19			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN20			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN21			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN22			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN23			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN24			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN25			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN26			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN27			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN28			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN29			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN30			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN31			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eUN32			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN01			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN02			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN03			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN04			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN05			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN06			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN07			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN08			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN09			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN10			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN11			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN12			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  
	{IO_INPUT_MV    , Ceu16WIO_eAN13			, 0 , 0 , 0     , 0     , 32000 , 0     , 0     , NULL},  

//  ##################################### Ausgänge Strommessung #####################################
    {IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_01	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_02	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_03	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_04	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_05	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_06	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_07	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_08	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_09	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_10	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_11	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM2_12	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM4_01	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM4_02	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM4_03	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM4_04	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM4_05	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM4_06	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM4_07	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_PWM4_08	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_01	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_02	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_03	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_04	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_05	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_06	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_07	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_08	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_09	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_10	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_11	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_12	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_13	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG2_14	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_01	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_02	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_03	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_04	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_05	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_06	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_07	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_08	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_09	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_10	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_11	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_12	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_13	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_14	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_15	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_16	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_17	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_18	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_19	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eHSD_DIG4_20	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
    {IO_INPUT_CURR  , Ceu16WIO_eLSD_DIG_01	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eLSD_DIG_02	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eLSD_DIG_03	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eLSD_DIG_04	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eLSD_DIG_05	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eLSD_DIG_06	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eLSD_DIG_07	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
	{IO_INPUT_CURR  , Ceu16WIO_eLSD_DIG_08	    , 0 , 0 , 0     , 0     , 5000  , 0     , 0     , NULL},      
//  ##################################### Ausgänge Steuerung #####################################
    {IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_01	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_02	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_03	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_04	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_05	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_06	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_07	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_08	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_09	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_10	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_11	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM2_12	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM4_01	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM4_02	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM4_03	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM4_04	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM4_05	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM4_06	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM4_07	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_PROM , Ceu16WIO_eHSD_PWM4_08	    , 1 , 1 , 0     , 0     , 1000  , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_01	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_02	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_03	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_04	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_05	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_06	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_07	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_08	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_09	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_10	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_11	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_12	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_13	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG2_14	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_01	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_02	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_03	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_04	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_05	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_06	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_07	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_08	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_09	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_10	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_11	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_12	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_13	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_14	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_15	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_16	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_17	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_18	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_19	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eHSD_DIG4_20	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
    {IO_OUTPUT_SW   , Ceu16WIO_eLSD_DIG_01	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eLSD_DIG_02	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eLSD_DIG_03	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eLSD_DIG_04	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eLSD_DIG_05	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eLSD_DIG_06	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eLSD_DIG_07	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL},      
	{IO_OUTPUT_SW   , Ceu16WIO_eLSD_DIG_08	    , 1 , 1 , 0     , 0     , 1     , 0     , 0     , NULL}, 
	{IO_UNKOWN	, 0		, 0 , 0	, 0		, 0		, 0		, 0		, 0		, 0		}	// NIEMALS VERAENDERN!!!!
};


//############################################################# PUBLIC HAL Funktionen #################################################################
// Alle Hardware Abstraktion Handler müssen umgesetzt werden, damit die Library funktioniert!
ten_CanErrorList __common_ReadValue(uint8_t IOIndex, uint32_t *pValue, ten_IO_ParamListe ParameterTypeSelecotr);
ten_CanErrorList __common_WriteValue(uint8_t IOIndex, uint32_t newValue, ten_IO_ParamListe ParameterTypeSelecotr);

ten_CanErrorList    HAL_IO_GET_Input_mV         (uint8_t IOIndex, uint32_t *pValue)
{
    return __common_ReadValue(IOIndex, pValue, ParamRawVoltage);
}
ten_CanErrorList    HAL_IO_GET_Input_mA         (uint8_t IOIndex, uint32_t *pValue)
{
	return __common_ReadValue(IOIndex, pValue, ParamRawCurrent);
}
ten_CanErrorList    HAL_IO_GET_Output_ppm       (uint8_t IOIndex, uint32_t *pValue)
{
	return __common_ReadValue(IOIndex, pValue, ParamOutCmdDutyCycle);
}
ten_CanErrorList    HAL_IO_GET_Output_bool      (uint8_t IOIndex, uint32_t *pValue)
{
	return __common_ReadValue(IOIndex, pValue, ParamOutCmdDutyCycle);
}
ten_CanErrorList    HAL_IO_GET_Output_mA        (uint8_t IOIndex, uint32_t *pValue)
{
	return __common_ReadValue(IOIndex, pValue, ParamRawCurrent);
}
ten_CanErrorList    HAL_IO_SET_Output_ppm       (uint8_t IOIndex, uint32_t newValue)
{
	return __common_WriteValue(IOIndex, newValue, ParamOutCmdDutyCycle);
}
ten_CanErrorList    HAL_IO_SET_Output_bool      (uint8_t IOIndex, uint32_t newValue)
{
	return __common_WriteValue(IOIndex, newValue, ParamOutCmdDutyCycle);
}
ten_CanErrorList    HAL_IO_SET_Output_mA        (uint8_t IOIndex, uint32_t newValue)
{
	return CANIO_ERR_UNSUPPORTED;   // Diese Hardware hat keine direkte Strom-Regelung. Dies muss in Software geschehen.s
}
ten_CanErrorList    HAL_CAN_SendMsg             (tst_CANIO_Msg *Msg2Send)
{
    extern uint8_t     Generic_CAN_txCounter; 
    extern uint8_t     Generic_CAN_txOverFlow;
    uint8_t Data[8] = {0};
    TstWJ1939_eTPLMsgData NewMessage = {0};
    NewMessage.pu8Data = Data;
    HAL_ConvertTo(*Msg2Send, &NewMessage);
	if(s16WJ1939_eSendMsg_Exe(Du16WJ1939_eInstance1, &NewMessage) != Ds16WJ1939_eSuccess)
    {
        Generic_CAN_txOverFlow++;
        return CANIO_ERR_TX_FAIL;
    }
    else 
    {
        Generic_CAN_txCounter++;
        return CANIO_ERR_OK;
    }
}
ten_CanErrorList    HAL_update_SourceID         (uint8_t newSourceID)
{
    return CANIO_ERR_NOTIMPLEMENTED;
}
uint32_t            HAL_SYS_GET_Millis          (void)
{
	return (uint32_t) (u64WCore_eExecutionTime_Exe() / 1000);
}
void                HAL_SYS_Get_SerialNumber    (char* pBuffer, size_t sizeOfBuffer)
{
    int i=0;
    for(i=0; i< MINIMUM(sizeOfBuffer, Du16WInfo_eECUHWSerialNumberSize); i++)
    {
        pBuffer[i] = DstWInfo_eFactoryData.tu8ECUHWSerialNumber_Str[i];
    }
}
void                HAL_SYS_Get_ProjektVersion  (char* pBuffer, size_t sizeOfBuffer)
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
void                HAL_SYS_Get_pBSPversion     (char* pBuffer, size_t sizeOfBuffer)
{
    size_t pos = 0;
	pos += ASC_vPrintInteger(&pBuffer[pos], (void*) &DstWVersion_eBspSWIdent.u8V0, PIT_UNSIGNEDBYTE);
	pBuffer[pos] = '.'; pos++;
	pos += ASC_vPrintInteger(&pBuffer[pos], (void*) &DstWVersion_eBspSWIdent.u8V1, PIT_UNSIGNEDBYTE);
	pBuffer[pos] = '.'; pos++;
	pos += ASC_vPrintInteger(&pBuffer[pos], (void*) &DstWVersion_eBspSWIdent.u8V2, PIT_UNSIGNEDBYTE);
	pBuffer[pos] = '.'; pos++;
	pos += ASC_vPrintInteger(&pBuffer[pos], (void*) &DstWVersion_eBspSWIdent.u8V3, PIT_UNSIGNEDBYTE);
}
ten_CanErrorList    HAL_WRITE_EEP               (void)
{
	return CANIO_ERR_NOTIMPLEMENTED;
}
ten_CanErrorList    HAL_ConvertTo               (tst_CANIO_Msg Msg, TstWJ1939_eTPLMsgData* pDest)
{
    int i=0;	
    for(i=0; i<8; i++) pDest->pu8Data[i]  = Msg.data[i];
    pDest->u16Length    = Msg.len;
    

    // Welchen J1939 Nachrichten Typ haben
    if(( Msg.id & 0x00FF0000L) == 0x00EF0000L )
    {   // ==> Wir haben eine gerichtete proprietary Nachricht!
		pDest->u8Dst      	= (uint8_t)  (( Msg.id & 0x000000FFL)  >>  0);
        pDest->u8Addr       = (uint8_t)  (( Msg.id & 0x0000FF00L)  >>  8); 
        pDest->u16PGN       = (uint16_t) (( Msg.id & 0x00FF0000L)  >>  8);            
    }
    else
    {	
		pDest->u8Dst       	= (uint8_t)  (( Msg.id & 0x000000FFL)  >>  0);
		pDest->u8Addr       = 0;
        pDest->u16PGN       = (uint16_t)  (( Msg.id & 0x00FFFF00L)  >>  8);        
    }

    pDest->u8DataPage   = 0;    // Wir benutzen die datapage option nicht...
    pDest->u8PrioType   = 6;    // wir bekommen beim HAL_ConvertFrom nicht gesichert die Priority mit. Deshalb wird hier immer mit dieser gesendet.
    pDest->u8Remote     = 0; // Verboten im J1939 Bereich
	return CANIO_ERR_OK;
}
ten_CanErrorList    HAL_ConvertFrom             (TstWJ1939_eTPLMsgData Msg, tst_CANIO_Msg* pDest)
{
	int i=0;	
    for(i=0; i<8; i++) pDest->data[i]  = Msg.pu8Data[i];
    pDest->len = (uint8_t) Msg.u16Length;
    pDest->id = 0;
	// Welchen J1939 Nachrichten Typ haben
    if(( Msg.u16PGN & 0xFF00) == 0xEF00 )
    {   // ==> Wir haben eine gerichtete proprietary Nachricht!
		pDest->id       |= ((((uint32_t)Msg.u8Addr) & 0x000000FFL)  <<  0);
        pDest->id       |= ((((uint32_t)Msg.u8Dst ) & 0x000000FFL)  <<  8); 
        pDest->id       |= ((((uint32_t)Msg.u16PGN) & 0x0000FF00L)  <<  8);            
    }
    else
    {
		pDest->id       |= ((((uint32_t)Msg.u8Addr) & 0x000000FFL)  <<  0);
        
        pDest->id       |= ((((uint32_t)Msg.u16PGN) & 0x0000FFFFL)  <<  8);         
    }
		pDest->id       |= 0x18000000; // Wir bekommen die Priority nicht sicher mitgeteilt, weil die Erfinder dieser dollen Lib ein Feld doppelt benutzen, ohne mitzuteilen, wie man den Unterschied erkennt.
										// Deshalb müssen wir hier pauschal mit der standard Priority senden...
  
    
	return CANIO_ERR_OK;
}





//############################################################# USER CAN Command List #################################################################
// In den Lücken zwischen den "fixierten CMDS" , können eigene CAN Nachrichten eingefügt werden.
tst_CANIO_Msg CAN_0x11_INPUT_GET_Generic(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    uint32_t InputValue = 0;   
    uint8_t offset = 0; 
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    offset = CanRxMessage.data[0] - 0x11;
        
    if(HAL_IO_GET_Input((offset * 7) + 0, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[1] = (uint8_t) (InputValue / 100 );
    if(HAL_IO_GET_Input((offset * 7) + 1, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[2] = (uint8_t) (InputValue / 100 );
    if(HAL_IO_GET_Input((offset * 7) + 2, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[3] = (uint8_t) (InputValue / 100 );
    if(HAL_IO_GET_Input((offset * 7) + 3, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[4] = (uint8_t) (InputValue / 100 );
    if(HAL_IO_GET_Input((offset * 7) + 4, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[5] = (uint8_t) (InputValue / 100 );
    if(HAL_IO_GET_Input((offset * 7) + 5, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[6] = (uint8_t) (InputValue / 100 );
    if(HAL_IO_GET_Input((offset * 7) + 6, IO_INPUT_MV, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[7] = (uint8_t) (InputValue / 100 );
    return  CanTxMessage;
}

tst_CANIO_Msg CAN_0x18_OUTPUT_GETCURR_Generic(tst_CANIO_Msg CanRxMessage)
{
    tst_CANIO_Msg CanTxMessage = LIB_CAN_clear();
    uint32_t InputValue = 0;   
    uint8_t offset = 0; 
    CanTxMessage.id = LIB_CAN_Switch_RXTX(CanRxMessage.id);
    CanTxMessage.len = 8;
    
    CanTxMessage.data[0] = CanRxMessage.data[0]; // MUX0
    offset = CanRxMessage.data[0] - 0x18;
        
    if(HAL_IO_GET_Input(45 + (offset * 7) + 0, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[1] = (uint8_t) (InputValue / 20 );
    if(HAL_IO_GET_Input(45 + (offset * 7) + 1, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[2] = (uint8_t) (InputValue / 20 );
    if(HAL_IO_GET_Input(45 + (offset * 7) + 2, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[3] = (uint8_t) (InputValue / 20 );
    if(HAL_IO_GET_Input(45 + (offset * 7) + 3, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[4] = (uint8_t) (InputValue / 20 );
    if(HAL_IO_GET_Input(45 + (offset * 7) + 4, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[5] = (uint8_t) (InputValue / 20 );
    if(HAL_IO_GET_Input(45 + (offset * 7) + 5, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[6] = (uint8_t) (InputValue / 20 );
    if(HAL_IO_GET_Input(45 + (offset * 7) + 6, IO_INPUT_CURR, &InputValue) == CANIO_ERR_OK) CanTxMessage.data[7] = (uint8_t) (InputValue / 20 );
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
	{ 0x11	, 1 , 100	, 0 , 0 , CAN_0x11_INPUT_GET_Generic		}, 	// ACHTUNG!!! Anhand Mux wird automatisch durchgeschaltet
	{ 0x12	, 1 , 100	, 0 , 0 , CAN_0x11_INPUT_GET_Generic		},	// Deshalb der gleiche Delegate
	{ 0x13	, 1 , 100	, 0 , 0 , CAN_0x11_INPUT_GET_Generic		},
	{ 0x14	, 1 , 100	, 0 , 0 , CAN_0x11_INPUT_GET_Generic		},
	{ 0x15	, 1 , 100	, 0 , 0 , CAN_0x11_INPUT_GET_Generic		},
	{ 0x16	, 1 , 100	, 0 , 0 , CAN_0x11_INPUT_GET_Generic		},
	{ 0x17	, 1 , 100	, 0 , 0 , CAN_0x11_INPUT_GET_Generic		},
	{ 0x18	, 1 , 100	, 0 , 0 , CAN_0x18_OUTPUT_GETCURR_Generic	},
	{ 0x19	, 1 , 100	, 0 , 0 , CAN_0x18_OUTPUT_GETCURR_Generic	},
	{ 0x1A	, 1 , 100	, 0 , 0 , CAN_0x18_OUTPUT_GETCURR_Generic	},
	{ 0x1B	, 1 , 100	, 0 , 0 , CAN_0x18_OUTPUT_GETCURR_Generic	},
	{ 0x1C	, 1 , 100	, 0 , 0 , CAN_0x18_OUTPUT_GETCURR_Generic	},
	{ 0x1D	, 1 , 100	, 0 , 0 , CAN_0x18_OUTPUT_GETCURR_Generic	},
	{ 0x1E	, 1 , 100	, 0 , 0 , CAN_0x18_OUTPUT_GETCURR_Generic	},
	{ 0x1F	, 1 , 100	, 0 , 0 , CAN_0x18_OUTPUT_GETCURR_Generic	},
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
    ten_CanErrorList result;
    int32_t readValue = 0;
    uint16_t ParameterType = 0;
    if(IOIndex >= LIB_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    if(IO_getParameterTypeFromList(GenericIOList[IOIndex].HAL_ID, ParameterTypeSelecotr, &ParameterType) != ERR_OK) return CANIO_ERR_IOTYPE_DIFFERENT;    
    if(CES32WIO_2_tenProjectErrorList(GenericIOList[IOIndex].HAL_ID, s32WIO_eGetVal_Exe(GenericIOList[IOIndex].HAL_ID, ParameterType, &readValue)) != ERR_OK) return CANIO_ERR_READ_FAIL;
        
    *pValue = readValue;
    return CANIO_ERR_OK;
}
ten_CanErrorList __common_WriteValue(uint8_t IOIndex, uint32_t newValue, ten_IO_ParamListe ParameterTypeSelecotr)
{
    ten_CanErrorList result;
    uint16_t ParameterType = 0;
	if(IOIndex >= LIB_IO_GET_ListSize()) return CANIO_ERR_INDEX_OUTOFRANGE;
    if(IO_getParameterTypeFromList(GenericIOList[IOIndex].HAL_ID, ParameterTypeSelecotr, &ParameterType) != ERR_OK) return CANIO_ERR_IOTYPE_DIFFERENT;    
    if(CES32WIO_2_tenProjectErrorList(GenericIOList[IOIndex].HAL_ID, s32WIO_eSetVal_Exe(GenericIOList[IOIndex].HAL_ID, ParameterType, newValue)) != ERR_OK) return CANIO_ERR_READ_FAIL;
    
    return CANIO_ERR_OK;
}

