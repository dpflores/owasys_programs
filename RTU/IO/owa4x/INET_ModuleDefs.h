 #ifndef __INET_MODULEDEFS_H
  
    #define __INET_MODULEDEFS_H
  
    #ifdef __cplusplus
     extern "C"{
    #endif
  
    #include "owcomdefs.h"
    #include "owerrors.h"
  
    //*********************** DEFINITION SECTION
    //EVENT TYPES
    #define  INET_RELEASED              1 
    //BEARER TYPES
    #define  INET_BEARER_GPRS           1
    #define  INET_BEARER_ENHANCED_GPRS  2
    //OWASYS Definition
    #define  MAX_USER_SIZE         256
    #define  MAX_PWD_SIZE          256
    #define  MAX_IP_SIZE           39      //Ready for IPv6-> XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX
    #define  MAX_APN_SIZE          63
    //*********************** End of DEFINITION SECTION
  
    //*********************** TYPEDEF SECTION
    //Events Section
    typedef struct _INET_Events{
       unsigned char evType;
       int           evHandled;
    }INET_Events;
  
    //Configuration Section
    typedef struct _TINET_MODULE_CONFIGURATION{
       unsigned char  wBearer;                   
 //      int   wSignal;
       void* wBearerParameters;
       void  (*inet_action)( INET_Events * );
    }TINET_MODULE_CONFIGURATION;
    //Bearers Configuration
    //GPRS
    typedef struct _GPRS_CONFIGURATION{
       unsigned char gprsUser[ 20];             
       unsigned char gprsPass[ 20];             
       unsigned char gprsDNS1[ 20];             
       unsigned char gprsDNS2[ 20];             
       unsigned char gprsAPN [ 20];            
    }GPRS_CONFIGURATION;
    typedef struct _GPRS_ENHANCED_CONFIGURATION{
       unsigned char gprsUser[ MAX_USER_SIZE];        
       unsigned char gprsPass[ MAX_PWD_SIZE];         
       unsigned char gprsDNS1[ MAX_IP_SIZE + 1];      
       unsigned char gprsDNS2[ MAX_IP_SIZE + 1];      
       unsigned char gprsAPN [ MAX_APN_SIZE + 1];     
    }GPRS_ENHANCED_CONFIGURATION;
  
  
    int iNet_Initialize          ( void *wConfiguration);
  
    int iNet_Finalize            ( void);
  
    int iNet_IsActive            ( int *wActive);
  
    int iNet_Start               ( void);
  
    int iNet_GetVersion          ( unsigned char *wVersion);
  
    int iNet_GetIPAddress        ( char *wIPAddress);
  
    int iNet_GetDataCounters     ( long *wTxBytes, long *wRxBytes);
  
    //*********************** End of DEFINITION SECTION
  
    #ifdef __cplusplus
     }
    #endif
  
 #endif