  
 #ifndef __GPS2_MODULEDEFS_H
  
    #define __GPS2_MODULEDEFS_H
  
    #ifdef __cplusplus
     extern "C"{
    #endif
  
 //-----------------------------------------------------------------------//
 //System Includes
 //-----------------------------------------------------------------------//
    #include <dlfcn.h>
    #include <termios.h>
  
  
 //-----------------------------------------------------------------------//
 //Defines
 //-----------------------------------------------------------------------//
    #define     COM1     0
    #define     COM2     1
    #define     COM3     2
    #define     COM4     3
    #define     COM5     4
    #define     COM6     5
  
    #define     MAX_RECEIVER_NAME 20
    #define     MAX_PROTOCOL_NAME 10
  
    //ANTARIS Acquisition and Tracking sensitivity settings
    #define     NORMAL_ACQUISITION            0
    #define     FAST_ACQUISITION              1
    #define     HIGH_SENSITIVITY_ACQUISITION  2
  
    //Fixing Position mask flags
    #define FLAG_NONE     0x0000
    #define FLAG_NF       0x0001  
    #define FLAG_DR       0x0002  
    #define FLAG_G2       0x0004  
    #define FLAG_G3       0x0008  
    #define FLAG_D2       0x0010  
    #define FLAG_D3       0x0020  
    #define FLAG_RK       0x0040  
    #define FLAG_TT       0x0080  
    #define ALL_FIX_FLAGS (FLAG_NF | FLAG_DR | FLAG_G2 | FLAG_G3 | FLAG_D2 | FLAG_D3 | FLAG_RK | FLAG_TT)
  
    //Fix Status
    #define STATUS_NF       0  
    #define STATUS_DR       1  
    #define STATUS_G2       2  
    #define STATUS_G3       3  
    #define STATUS_D2       4  
    #define STATUS_D3       5  
    #define STATUS_RK       6  
    #define STATUS_TT       7  
 //-----------------------------------------------------------------------//
 //Type definitions
 //-----------------------------------------------------------------------//
  
    typedef enum {
       GGA=0,
       GLL=1,
       GSA=2,
       GSV=3,
       RMC=4,
       VTG=5,
       ZDA=7,
       PSRF161=9
    }MSGNMEA;
  
    typedef struct {
       unsigned short Degrees;
       unsigned char  Minutes;
       double         Seconds;
       char           Dir;
    }TGPS_COORD;
  
    typedef struct {   //Geodetic position type
       TGPS_COORD  Latitude,
                   Longitude;
       int         DataValid;
    }TGPS_POS;
  
    typedef struct {   //Speed and course type
       float  speed_in_knots;
       float  speed_in_mph;
       float  speed_in_kmh;
       float  course_over_ground;
    }TGPS_SPEED;
  
    typedef enum {
       RATE_NO_MSG,
       RATE_POSITION,
       RATE_SPEED,
       RATE_GGA,
       RATE_GLL,
       RATE_GSA,
       RATE_GSV,
       RATE_RMC,
       RATE_VTG,
       RATE_ZDA,
       RATE_PSRF161,
       RATE_MSS
    }rateMsgType_e;
  
    typedef struct {
       rateMsgType_e   rateMsgType;
       TGPS_POS        Coordenates;
       TGPS_SPEED      Speed;
       char            Message[256];
    }TRATE_MESSAGE;
  
    typedef struct {   //GPS module configuration type
       char          DeviceReceiverName[MAX_RECEIVER_NAME];
       speed_t       ParamBaud;
       int           ParamParity;
       unsigned char ParamLength;
       char          ProtocolName[MAX_PROTOCOL_NAME];
       unsigned char GPSPort;
    } TGPS_MODULE_CONFIGURATION;
  
    typedef enum {     //antenna status possible values for TIM gps
       ANTENNA_ON_OK = 0,
       OPEN_CIRCUIT,
       SHORT_CIRCUIT,
       ANTENNA_OFF,
       PASSIVE_ANTENNA,
       VALUE_NOT_VALID
    }AntennaStatusValue;
  
    typedef  struct {    //TIM antenna status type
       AntennaStatusValue Status;
       unsigned char      AGC;
    }TANTENNA_STATUS;
  
    typedef enum {       //antenna status possible values for new Antaris gps
       INIT = 0,
       STATUS_DONTKNOW,  
       OK,               
       SHORTCIRCUIT,     
       OPEN              
    }tAntennaStatusValue;
  
    typedef enum {       //antenna power state possible values for new Antaris gps
       OFF = 0,
       ON,
       POWER_DONTKNOW
    }tAntennaPowerValue;
  
    typedef struct {      //ANTARIS antenna status type
       tAntennaStatusValue  A_Status;
       tAntennaPowerValue   A_Power;
    }tANTENNA_NEW_STATUS;
  
    typedef enum {
       HOT_START = 1,
       WARM_START,
       WARM_START_WITH_INIT,
       COLD_START,
       CLEAR_MEMORY = 8
    }START_TYPE;
    typedef struct {
       unsigned char Hours;     
       unsigned char Minutes;   
       float         Seconds;   
       unsigned char Day;       
       unsigned char Month;     
       int           Year;      
    }TUTC_DATE_TIME;
    typedef struct {
       int    Px;         
       int    Py;         
       int    Pz;         
       int    Vx;         
       int    Vy;         
       int    Vz;         
    }tECEF_COORDINATES;
    typedef struct {
       int    Odom;     
       double Gyro;     
       double Temp;     
    }tESF_MEAS;
    typedef struct {
       double        East;         
       unsigned char LongitudeDir; 
       double        North;        
       unsigned char Hemisphere;   
       unsigned char Zone;         
       double        Altitude;     
       char          NavStatus[3]; 
    }tUTM_COORDINATES;
    typedef struct {
       TGPS_COORD  Latitude,        
                   Longitude;       
       double      Altitude;        
       char        NavStatus[3];    
    }tGEODETIC_COORDINATES;
    typedef struct {
       unsigned char PosFixMode;  // Position fix mode (0= No fix, 1=DR fix, 2=G2 fix, 3=G3 fix,
                                  // 4=D2 fix, 5=D3 fix, 6=RK fix, 7=TT fix
       float         TDOP;        
       float         HDOP;        
       float         VDOP;        
    }tGNSS_DOP_SV;
    typedef struct {
       unsigned char SV_Id;         
       unsigned char SV_Elevation;  
       short int     SV_Azimuth;    
       char          SV_SNR;        
    }tSV_Data;
  
    typedef struct {   //GNSS SV in view type
       unsigned char SV_InView;
       tSV_Data      SV[64];
    }tGSV_Data;
  
    typedef struct {  //Datum parameters
          short   datumNum;
          char    datumName[6];
          double  majA;
          double  flat;
          float    dX;
          float    dY;
          float    dZ;
          float    rotX;
          float    rotY;
          float    rotZ;
          float    scale;
       }tDATUM;
    typedef struct {
       unsigned char  PosValid;         
       unsigned char  OldValue;         
       TGPS_COORD     Latitude,         
                      Longitude;        
       double         Altitude;         
       char           NavStatus[3];     
       double         HorizAccu;        
       double         VertiAccu;        
       double         Speed;            
       double         Course;           
       double         HDOP;             
       double         VDOP;             
       double         TDOP;             
       unsigned char  numSvs;           
       double         LatDecimal;       
       double         LonDecimal;       
    }tPOSITION_DATA;
  
    typedef struct {    //Survey-in data
       unsigned int TimeOfWeek;      
       char SurveyStatus;            
       char MeanPosValid;            
       unsigned int ObservationTime; 
       unsigned int PositionsUsed;   
       double MeanPosAcc;            
       double meanX;                 
       double meanY;                 
       double meanZ;                 
    }tNAV_SVIN_DATA;
  
    typedef struct {           //TMODE3 data
       unsigned char  mode;          
       char           units;         
       double         ecefX;         
       double         ecefY;         
       double         ecefZ;         
       double         FixPosAccu;    
       unsigned int   svinMinDur;    
       double         SurveyPosAccu; 
    }t_TMODE3_DATA;
  
    typedef struct {    //UBX-NAV-SOL data
       unsigned char  OldValue;      
       double         TimeOfWeek;    
       short int      WeekNumber;    
       unsigned char  gpsFix;        
       char           flags;         
       double         ecefX;         
       double         ecefY;         
       double         ecefZ;         
       double         PosAccu;       
       double         ecefVX;        
       double         ecefVY;        
       double         ecefVZ;        
       double         SpeedAccu;     
       int            PositionDOP;   
       unsigned char  numSV;         
    }tNAV_SOL_DATA;
  
    int GPS_Initialize( void *wConfiguration );
  
    int GPS_Start( void );
  
    int GPS_IsActive( int *wActive );
  
    int GPS_Finalize( void );
  
    int GPS_GetVersion( unsigned char *wVersion );
  
    int GPS_GetAllPositionData( tPOSITION_DATA *pCurCoords );
  
    int GPS_GetPosition_Polling( TGPS_POS *pCurCoords );
  
    int GPS_GetSpeedCourse_Polling( TGPS_SPEED *pCurSpeed );
  
    int GPS_GetUTCDateTime( TUTC_DATE_TIME *pDateTime );
  
    int GPS_GetStatusAntenna( tANTENNA_NEW_STATUS *pStatus );
  
    int GPS_GetGeodetic_Coordinates( tGEODETIC_COORDINATES *pGEODETIC_Coord );
  
    int GPS_GetSV_inView( tGSV_Data *pData );
  
    int GPS_Get_Software_Version( char *pData );
  
    int GPS_Configure_ITFM( char mode, char bbthres, char cwthres );
  
    int GPS_GetStatusJamming( char *pStatus );
  
    int GPS_SetNavigationConfig( unsigned char MinSV, unsigned char MinEle, short int PDOP );
  
    int GPS_SetFixConfig( short int wMask, unsigned int wHAccu);
  
    int GPS_GetFixConfig( short int *pMask, unsigned int *pHAccu);
  
    int GPS_Get_Model( char *pBuffer );
  
    int GPS_GetRELPOSNED_Data( char *pBuffer, int *pLen ); // ****
  
    int GPS_Send_DGPS_Message( char *pMessage, int Len );
  
    int GPS_GetCFG_NAV( char *pBuffer, int *pLen ); // ****
  
    int GPS_GetNAVX5_Data( char *pBuffer, int *pLen ); // ****
  
    int GPS_SetANA( char mode);
  
    int GPS_SetGpsMode( char GpsMode );
  
    int GPS_SetDynamicModel( char DynamicModel );
  
    int GPS_SetStaticThreshold( unsigned char Threshold );
  
    int GPS_GetDOP_FixMode( tGNSS_DOP_SV *pDOP_SV ); // ****
  
    int GPS_GetECEF_Coordinates( tECEF_COORDINATES *pECEF_Coord );
  
    int GPS_SetMeasurementRate( char measRate);
  
    int GPS_GetMeasurementRate( char *measRate);
  
    int GPS_EnableRTCM3( char mask, void(*wHandler)( char *, int) );
  
    int GPS_SetTMODE3_Fix( double ecefx, double ecefy, double ecefz, double accuracy ); // ****
  
    int GPS_SetTMODE3_Survey( unsigned int seconds, double accuracy ); // ****
  
    int GPS_SetTMODE3_Disable( void ); // ****
  
    int GPS_Get_TMODE3( t_TMODE3_DATA *pData );
  
    int GPS_GetNAV_SVIN( tNAV_SVIN_DATA *pData );
  
    int GPS_GetNAV_SOL( tNAV_SOL_DATA *pData );
  
    int GPS_Set_Led_Mode( unsigned char wMode );
  
    #ifdef __cplusplus
     }
    #endif
  
 #endif