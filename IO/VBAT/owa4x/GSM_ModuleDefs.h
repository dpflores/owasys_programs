 #ifndef __GSM_MODULEDEFS_H
  
    #define __GSM_MODULEDEFS_H
  
    #ifdef __cplusplus
     extern "C"{
    #endif
  
    #include "owcomdefs.h"
    #include "owerrors.h"
  
    //Call Control Section
    #define CALL_TYPE_VOICE    1
    #define CALL_TYPE_USSD     2
    #define CALL_TYPE_DATA     3
    #define CALL_TYPE_GPRS     4
    #define CALL_TYPE_SOS      5
  
    //SMS Section
    #define MAX_BODY_SIZE      160
    #define MAX_PHONE_SIZE     20
  
    #define REC_UNREAD         0
    #define REC_READ           1
    #define STO_UNSENT         2
    #define STO_SENT           3
  
    typedef struct _DATETIME{
       unsigned char   year;
       unsigned char   month;
       unsigned char   day;
       unsigned char   hour;
       unsigned char   minute;
       unsigned char   second;
       unsigned char   timeZone;
    }DATETIME;
  
    typedef struct _SMS_t{  
       unsigned char owIndex;
       unsigned char owBody[MAX_BODY_SIZE + 1];
       unsigned char owBodySize;
       unsigned char owSMSType;
       unsigned char owSA_DA[ MAX_PHONE_SIZE];
       DATETIME      owSCDateTime;
    }SMS_s;
  
    typedef struct _SMSExtended_t{  
       unsigned int  owIndex;
       unsigned char owBody[MAX_BODY_SIZE + 1];
       unsigned char owBodySize;
       unsigned char owSMSType;
       unsigned char owSA_DA[ MAX_PHONE_SIZE];
       DATETIME      owSCDateTime;
    }SMSExtended_s;
    //PhoneBook
    #define PB_SIM          1
    #define PB_ME           2
    #define PB_REC_CALLS    3
    #define PB_MIS_CALLS    4
    #define PB_LAST_CALLS   5
    #define PB_OWN_NUMBERS  6
    #define PB_FIXED_NUMS   7
    #define PB_SERVICE_NUM  8
  
    #define PB_INIT_AT_RESET      0
    #define PB_NO_INIT_AT_RESET   1
  
    //OWN NUMBERS
    #define OWN_VOICE       1
    #define OWN_FAX         2
    #define OWN_DATA        3
  
    #define MAX_NAME_SIZE   20
    #define MAX_PHONE_SIZE  20
  
    typedef struct _GSM_PhoneBook_t{
       unsigned char  owFolder;
       unsigned short owPos;
       unsigned char  owPhone[ MAX_PHONE_SIZE];
       unsigned char  owName [ MAX_NAME_SIZE];
    }GSM_PhoneBook_t;
  
    //Call Information
    typedef struct _GSM_CallEntry_t{
       unsigned char owPos;
       unsigned char owPhone[ 20];
       DATETIME      owCallDate;
    }GSM_CallEntry_t;
  
    typedef unsigned char* Phone_t;
    //GSM Services
    //RESTRICTED CALLS - TO EXPORT
    #define  ALL_OUT           1
    #define  ALL_INOUT         2
    #define  ALL_INOUT_ABROAD  3
    #define  ALL_IN            4
    #define  IN_ABROAD         5
    #define  ALL_CALLS         6     //Only for Deactivation
    //DIVERT CALLS --> TO EXPORT
       //Type
    #define  DV_ALL                  0
    #define  DV_BUSY                 1
    #define  DV_NO_REPLY             2
    #define  DV_NO_REACHABLE         3
    #define  DV_ALL_FORWARD          4  //(includes 0,1,2 and 3)
    #define  DV_ALL_COND_FORWARD     5  //(includes 1,2 and 3)
    //Classes
    //class> is a sum of integers each representing a class of information
    //(default 7=voice&data&fax):
    #define  CLASS_VOICE             1
    #define  CLASS_DATA              2
    #define  CLASS_FAX               4
    #define  CLASS_SMS               8
    #define  CLASS_DATA_SYNC        16
    #define  CLASS_DATA_ASYNC       32
  
    typedef struct _GSM_DivertCall_t{
       unsigned char owStatus;
       unsigned char owPhone[ 20];
    }GSM_DivertCall_t;
    typedef struct _GSM_Operator_t{
       unsigned char  owStatus;        
       unsigned char  owOperName[ 20]; 
       unsigned short owPLMN;          
    }GSM_Operator_t;
    typedef struct _GSM_OperatorExtended_t{
       unsigned char owStatus;        
       unsigned char owOperName[ 20]; 
       unsigned long owPLMN;          
    }GSM_OperatorExtended_t;
  
    typedef struct _GSM_Operator3G_t{
       unsigned char owStatus;        
       unsigned char owOperName[ 20]; 
       unsigned long owPLMN;          
       unsigned char owNetwork;       
    }GSM_Operator3G_t;
  
    typedef GSM_Operator3G_t GSM_OperatorGeneric_t;
  
    //owStatus Possible Values
    #define  OP_UNKNOWN              0
    #define  OP_AVAILABLE            1
    #define  OP_CURRENT              2
    #define  OP_FORBIDDEN            3
    //OPERATOR Selection:
    #define  OP_AUTOSEL              0
    #define  OP_ONLYMANUAL           1 //Tries to make a Manual Net Selection,
    #define  OP_MANUALSEL            4 //Tries to make a Manual Net Selection, if fails remains automatic.
    //Radio Access Technology(RAT)
    #define  RAT_GSM                 0   //GSM
    #define  RAT_GSM_UMTS            1   //Dual mode GSM/UMTS
    #define  RAT_UMTS                2   //UMTS
    #define  RAT_LTE                 3   //LTE
    #define  RAT_UMTS_LTE            4   //Dual mode UMTS/LTE
    #define  RAT_GSM_LTE             5   //Dual mode GSM/LTE
    #define  RAT_GSM_UMTS_LTE        6   //Triple mode GSM/UMTS/LTE
       #define  RAT_E_UMTS              7   //E-UTRAN
  
  
    typedef struct _GSM_Cell_t{
       unsigned short owLac;         
       unsigned short owCellId;      
    }GSM_Cell_t;
  
    typedef struct _GSM_CellExtended_t{
       int     owLac;         
       int     owCellId;      
    }GSM_CellExtended_t;
  
    typedef struct _GSM_CellAndRAT_t{
       int     owLac;         
       int     owCellId;      
       char    owRAT;         
    }GSM_CellAndRAT_t;
    //Events Section
  
  typedef enum _gsmEvent_e{
       GSM_NO_SIGNAL = 0, 
       GSM_RING_VOICE, 
       GSM_RING_DATA, 
       GSM_NEW_SMS, 
       GSM_CALL_RELEASED, 
       GSM_RECEIVED_DATA, 
       GSM_FAILURE, 
       GSM_COVERAGE, 
       GSM_HIGHER_TEMP, 
       GSM_STOP_SENDING_DATA, 
       GSM_START_SENDING_DATA, 
       GSM_CALL_WAITING, 
       GSM_USSD_INFO, 
       GSM_USSD_ERROR, 
       GSM_USSD_REPLY, 
 //      GSM_AOC,
 //      GSM_SS_INDICATION,
       GSM_CONNECTED_LINE, 
       GSM_GPRS_COVERAGE, 
       GSM_RING_END, 
       GSM_MEM_SMS_FULL, 
       GSM_MEM_SMS_AVAI, 
       GSM_BOARD_TEMP, 
       GSM_POSSIBLE_JAMMING, 
       GSM_JAMMING_INDICATION, 
       GSM_SMS_SENT_INDEX, 
       GSM_SMS_DELIVER_REPORT, 
       GSM_END_OF_JAMMING, 
       EPS_NETWORK_STATUS, 
    }gsmEvent_e;
    //COVERAGE DEFINITIONS
    #define NO_NETWORK            0
    #define REGISTERED            1
    #define REGISTER_BUT_ROAMING  2
    #define SOS_ONLY              3
    #define NETWORK_SEARCH        4
  
    #define GPRS_NO_NETWORK       0
    #define GPRS_REGISTERED       1
    #define GPRS_SEARCHING        2
    #define GPRS_REGISTERED_ROAM  5
  
    #define EPS_NO_NETWORK        0
    #define EPS_REGISTERED        1
    #define EPS_SEARCHING         2
    #define EPS_DENIED            3
    #define EPS_UNKNOWN           4
    #define EPS_REGISTERED_ROAM   5
    #define EPS_EMERGENCY_BEARER  8
  
  
    //EVENT BUFFER
    #define EVENTS_BUFFER_SIZE    1024
  
    typedef struct _gsmEvents_s{
       gsmEvent_e  gsmEventType;
       char        evBuffer[ EVENTS_BUFFER_SIZE];
       int         evHandled;
    }gsmEvents_s;
  
    typedef struct _TGSM_MODULE_CONFIGURATION{
       unsigned char wCode    [ 9];
       unsigned char wMECode  [ 9];
       void  (*gsm_action)( gsmEvents_s * );
    }TGSM_MODULE_CONFIGURATION;
  
    typedef struct _GSM_CurrentCall_t{
       unsigned char owPhone     [ MAX_PHONE_SIZE];
       unsigned char owAlphaTag  [ MAX_PHONE_SIZE];
       unsigned char  owCallDir;
       unsigned char  owCallIndex;
       unsigned char  owCallStatus;
       unsigned char  owCallClass;
       unsigned char  owMpty;
       unsigned char  owType;
    }GSM_CurrentCall_t;
  
    //Miscellaneous
    #define CALL_ON_VOICE      0
    #define CALL_ON_CALL       1
    #define CALL_ON_GPRS       2
  
    #define LOG_FILE_NAME_SIZE 128
  
    int GSM_Initialize( void *wConfiguration);
  
    int GSM_Finalize( void);
  
    int GSM_IsActive( int *wActive);
  
    int GSM_Start( void);
  
    int GSM_GetVersion( unsigned char *wVersion);
  
    int GSM_SendCommand( char* gsmCommand);
  
    int GSM_SendData( unsigned char* wBuffer, int wSize);
  
    int GSM_ReceiveData( unsigned char* wBuffer, int wSize);
  
    int GSM_Dial( char wType, unsigned char* wBuffer);
  
    int GSM_HangUp( void );
  
    int GSM_AnswerCall( void );
  
    int GSM_SetVolume( unsigned char wSense);
  
    int GSM_SetRingVolume( unsigned char wTone, unsigned char wVolume);
  
    int GSM_SetTxGain( unsigned char wGain, unsigned int wAtten);
  
    int GSM_SetMicroMute( unsigned char wMute);
  
    int GSM_PlayDTMF( unsigned char wTone);
  
    int GSM_ActivateRegistration( char wRegistration);
  
    int GSM_GetSignalStrength( unsigned char* wSignalStrength);
  
    int GSM_GetSignalQuality( unsigned char* wSignalQuality);
  
    int GSM_GetCellPosition( GSM_Cell_t* wCellPosition);
  
    int GSM_GetRegistration( char* wRegistration);
  
    int GSM_AttachGPRS( char wEnable);
  
    int GSM_GetGPRSRegistration( unsigned char* wRegistration);
  
    int GSM_GetNetworkSelectionModeExtended( unsigned char* wMode, unsigned long* wOper);
  
    int GSM_GetNetworksListExtended( GSM_OperatorExtended_t** wOperatorListInfo, unsigned char* wSize);
  
    int GSM_SetNetworkSelectionExtended( unsigned char wMode, unsigned long wOper);
  
    int GSM_FindContact( GSM_PhoneBook_t* wBuffer, unsigned short wPos);
  
    int GSM_WriteContact( GSM_PhoneBook_t wBuffer);
  
    int GSM_DeleteContact( unsigned short wPos, unsigned char wPBStorage);
  
    int GSM_ReadMyNumber( unsigned char* wBuffer, unsigned char* wSize, unsigned char wNumberType);
  
    int GSM_ChangeMyNumber( unsigned char* wBuffer, unsigned char wNumberType);
  
    int GSM_ReadSIMPhoneBook( GSM_PhoneBook_t** wBuffer, unsigned short* wSize);
  
    int GSM_ReadMEPhoneBook( GSM_PhoneBook_t** wBuffer, unsigned short* wSize);
  
    int GSM_ReadLastDialledCall( GSM_CallEntry_t** wBuffer, unsigned char* wSize, unsigned char wPos);
  
    int GSM_ReadMissedCall( GSM_CallEntry_t** wBuffer, unsigned char* wSize, unsigned char wPos);
  
    int GSM_ReadReceivedCall( GSM_CallEntry_t** wBuffer, unsigned char* wSize, unsigned char wPos);
  
    int GSM_ReadSMS( SMS_s* wBuffer, unsigned char* wSize, char wPos, char wFolder);
  
    int GSM_ReadSMSExtended( SMSExtended_s* wBuffer, unsigned char* wSize, int wPos, char wFolder);
  
    int GSM_DeleteSMS( char wPos, char wFolder );
  
    int GSM_DeleteSMSExtended( int wPos, char wFolder );
  
    int GSM_SendSMS( unsigned char* wBuffer,unsigned char* wDestination, char wIndex);
  
    int GSM_SendSMSExtended( unsigned char* wBuffer,unsigned char* wDestination, int wIndex);
  
    int GSM_SendSMSBySize( unsigned char* wBuffer,int wSize,unsigned char* wDestination, char wIndex);
  
    int GSM_SendSMSExtendedBySize( unsigned char* wBuffer,int wSize,unsigned char* wDestination, int wIndex);
  
    int GSM_WriteSMSToMemory( unsigned char* wBuffer,unsigned char* wDestination, unsigned char* wIndex );
  
    int GSM_WriteSMSToMemoryExtended( unsigned char* wBuffer,unsigned char* wDestination, int* wIndex );
  
    int GSM_ReadSMSCentreAddress( unsigned char* wBuffer, unsigned char *wSize);
  
    int GSM_WriteSMSCentreAddress( unsigned char* wBuffer);
  
    int GSM_SMSIndications( char wStatus);
  
    int GSM_SMSStatus( int* wSMSBusy, int* wSMSTotal);
  
    int GSM_ReadPDUSMS( unsigned char *wBuffer, unsigned char *wSize, unsigned char *wStatus, unsigned char  wPos, unsigned char wFolder);
  
    int GSM_ReadPDUSMSExtended( unsigned char *wBuffer, unsigned char *wSize, unsigned char *wStatus, int  wPos, unsigned char wFolder);
  
    int GSM_SendPDUSMS( unsigned char *wBuffer);
  
    int GSM_WritePDUSMSToMemory( unsigned char *wBuffer, unsigned char *wIndex);
  
    int GSM_WritePDUSMSToMemoryExtended( unsigned char *wBuffer, int *wIndex);
  
    int GSM_SetUSSD( unsigned char wStatus);
  
    int GSM_ReplyUSSD( unsigned char* wReply);
  
    int GSM_GetDateTime( DATETIME* wDateTime);
  
    int GSM_SetDateTime( DATETIME* wDateTime);
  
    int GSM_GetIMEI( char* wImei, int wSize);
  
    int GSM_GetIMSI ( char* wImsi, int wSize);
  
    int GSM_GetAudioModel( void);
  
    int GSM_ActivateCardCodes( unsigned char* wCode, unsigned char wStatus);
  
    int GSM_ModifyPINCode( unsigned char* wOldCode, unsigned char* wNewCode);
  
    int GSM_ActivatePhoneCodes( unsigned char* wCode, unsigned char wStatus);
  
    int GSM_ModifyPhoneCode( unsigned char* wOldCode, unsigned char* wNewCode);
  
    int GSM_CheckPINProtection( unsigned char* wStatus);
  
    int GSM_CheckPhoneProtection( unsigned char* wStatus);
  
    int GSM_ModifyBarringCode( unsigned char wFacility, unsigned char* wOldCode, unsigned char* wNewCode);
  
    int GSM_ShowNumberAtNextCall( unsigned char wShow);
  
    int GSM_GetShowNumberAtNextCall( unsigned char *wShow);
  
    int GSM_SetDivertCall( unsigned char wType, unsigned char* wNumber, unsigned char wStatus, unsigned char wClass);
  
    int GSM_GetDivertCall( GSM_DivertCall_t** wDivert, unsigned char* wSize, unsigned char wReason);
  
    int GSM_SetRestrictedCall( unsigned char wType, unsigned char wStatus, unsigned char* wPassword);
  
    int GSM_GetRestrictedCall( int** wRestricted, unsigned char* wSize, unsigned char wRestrictedType);
  
    int GSM_SetWaitingCall( unsigned char wStatus, unsigned char wMode);
  
    int GSM_GetWaitingCall( unsigned char* wStatus);
  
    int GSM_SetConnectedLinePresentation( unsigned char wStatus);
  
    int GSM_SetJamming( unsigned char wValue);
  
    int GSM_GetCellPositionExtended( GSM_CellExtended_t* wCellPosition);
  
    int GSM_GetCellAndRAT( GSM_CellAndRAT_t* wCellAndRAT);
  
    int GSM_GetNetworkSelectionMode3G( unsigned char* wMode, unsigned long* wOper, unsigned char* wNet);
  
    int GSM_SetNetworkSelection3G( unsigned char wMode, unsigned long wOper, unsigned char wNet);
  
    int GSM_GetNetworksList3G( GSM_Operator3G_t** wOperatorListInfo, unsigned char* wSize);
  
    int GSM_GetNetworkSelectionModeGeneric( unsigned char* wMode, unsigned long* wOper, unsigned char* wNet);
  
    int GSM_GetNetworksListGeneric( GSM_OperatorGeneric_t** wOperatorListInfo, unsigned char* wSize);
  
    int GSM_SetNetworkSelectionGeneric( unsigned char wMode, unsigned long wOper, unsigned char wNet);
  
    int GSM_Set_Led_Mode( unsigned char wMode);
  
    int GSM_Set_SIM_DualMode( unsigned char wValue);
  
    int GSM_Get_SIM_DualMode( unsigned char *wValue);
  
    int GSM_Switch_SIMCARD( unsigned char wValue);
  
    int GSM_Get_Active_SIMCARD( unsigned char *wValue);
  
 int GSM_GetModuleModel( unsigned char *wModel);
  
 int GSM_SetLogFile( unsigned char enable, unsigned char *wName, unsigned int size);
  
 int GSM_GetSpecificError( int *errnumber);
  
 int GSM_ClearSpecificError( void);
  
 int GSM_DefinePDPContext( TGSM_MODULE_CONFIGURATION *pConfiguration);
  
    int GSM_GetEPSRegistration( unsigned char* wRegistration);
  
    int GSM_SetDataCentric( int wMode, int *wChange);
  
    #ifdef __cplusplus
     }
    #endif
  
 #endif