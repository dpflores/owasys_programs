//*********************************************************************
//*************  Copyright (C) 2008        OWASYS  ********************
//*********************************************************************
//**
//** The copyright to the computer programs here in is the property of
//** OWASYS The programs may be used and/or copied only with the
//** written permission from OWASYS or in accordance with the terms and
//** conditions stipulated in the agreement/contract under which the
//** programs have been supplied.
//**
//*********************************************************************
//******************** Module information *****************************
//**
//** Project:
//** Description:
//**
//** Filename:      Test_GPS_Module.cpp
//** Owner:         OWASYS
//** Creation date: 01/04/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//*********************************************************************

#define __TEST_GPS_Module_CPP

//-----------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------//
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <mosquitto.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>

//-----------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------//
#include "Test_GPS_Module.h"
#include "rtu_module.h"
#include "io_module.h"
#include "gps_module.h"

#include "owa4x/owerrors.h"

// To use time library of C
#include <time.h>

#include <stdlib.h>
//-----------------------------------------------------------------//
//Defines
//-----------------------------------------------------------------//

//-----------------------------------------------------------------//
//Macros
//-----------------------------------------------------------------//


//-----------------------------------------------------------------//
//External variables
//-----------------------------------------------------------------//


//-----------------------------------------------------------------//
//External functions
//-----------------------------------------------------------------//


//-----------------------------------------------------------------//
//Private variables
//-----------------------------------------------------------------//
// File descriptor for logging.
FILE *logfd = NULL;
//
//#define MQTT_HOSTNAME "owasys.com"
//#define MQTT_PORT 1883
//#define MQTT_TOPIC "g"
//#define MQTT_TOPIC2 "b"
//
//typedef struct {
//      int  len;          // Message lenght
//      char msg[512];     // Message data
//}t_RTCM3_DATA;
//
//
////static struct mosquitto *mosq = NULL;
//static pthread_t RTCM3Events; //, CreateKMLFile;
//BOOL runRTCM3Handler = FALSE;
//BOOL runKMLFile = FALSE;
//static sem_t RTCM3EventsSem;
//char KmlNameFile[128];
//
//static t_RTCM3_DATA RTCM3BufferData[10];
//static unsigned char RTCM3EventsWr, RTCM3EventsRd;

/* functions definition */

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

//-----------------------------------------------------------------//
// Function: GetGPSPosition()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the gps position.
//    If position fix is not valid the corresponding tag is set to FALSE.
//-----------------------------------------------------------------//


void GetGPSPosition( void )
{
	int   ReturnCode = 0;
   ReturnCode = GPS_GetPosition_Polling( &CurCoords );
   if( ReturnCode != NO_ERROR )
      RES_( printf( "Error %d in GPS_GetPosition_Polling()...\n", ReturnCode);)
   else {
      if (CurCoords.DataValid == TRUE) {
         RES_( printf( "\n-------------------------------------------------------\n");)
         RES_( printf ("LATITUDE  --> %02hu degrees %02hhu minutes %04.04f seconds %c\n",
                        CurCoords.Latitude.Degrees, CurCoords.Latitude.Minutes,
                        CurCoords.Latitude.Seconds, CurCoords.Latitude.Dir); )
         RES_( printf ("LONGITUDE --> %03hu degrees %02hhu minutes %04.04f seconds %c\n",
                        CurCoords.Longitude.Degrees, CurCoords.Longitude.Minutes,
                        CurCoords.Longitude.Seconds, CurCoords.Longitude.Dir); )
         RES_( printf( "-------------------------------------------------------\n");)
      }
      else
         RES_( printf( "\nPOSITION NOT VALID\n");)	
      }
}

void GetFullGPSPosition( void )
{
	int   ReturnCode = 0;
	tPOSITION_DATA LocalCoords;
	static int NumOld = 0;

   ReturnCode = GPS_GetAllPositionData( &LocalCoords );
   if( ReturnCode != NO_ERROR )
      printf( "Error %d in GPS_GetAllPositionData()...\n", ReturnCode);
   else {
		if( LocalCoords.OldValue != 0){
			NumOld++;
		}
		printf("{\"pos_valid\": %hhu, \"old_pos\": %hhu, \"total\": %d, \"nav_status\": \"%s\", \"lat\": %.7lf, \"lon\": %.7lf, \"alt\": %04.03f, \"hAcc\": %04.01f, \"vAcc\": %04.01f, \"Speed\": %04.03f, \"Course\": %04.02f, \"HDOP\": %4.03f, \"VDOP\": %4.01f, \"TDOP\": %4.01f, \"numSvs\": %hhu}",
            LocalCoords.PosValid, LocalCoords.OldValue, NumOld, LocalCoords.NavStatus, LocalCoords.LatDecimal, LocalCoords.LonDecimal,
             LocalCoords.Altitude, LocalCoords.HorizAccu, LocalCoords.VertiAccu, LocalCoords.Speed,LocalCoords.Course, LocalCoords.HDOP,
             LocalCoords.VDOP, LocalCoords.TDOP, LocalCoords.numSvs);
      fflush(stdout); // Asegurar que se envía el contenido al buffer de salida
	
	}
}

//-----------------------------------------------------------------//
// Function: GetGPSSpeed()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the gps speed and course.
//-----------------------------------------------------------------//
void GetGPSSpeed( void )
{
	int   ReturnCode = 0;

	ReturnCode = GPS_GetSpeedCourse_Polling( &CurSpeed );
	if(ReturnCode != NO_ERROR)
		RES_( printf( "Error %d in GPS_GetSpeedCourse_Polling()...\n", ReturnCode);)
   else {
   	RES_( printf( "\n--------------------------------------------\n");)
  	   RES_( printf ("speed in knots = %04.04f\n", CurSpeed.speed_in_knots);)
		RES_( printf ("speed in kmh = %04.04f\n", CurSpeed.speed_in_kmh);)
		RES_( printf ("speed in mph = %04.04f\n", CurSpeed.speed_in_mph);)
		RES_( printf ("course = %04.04f\n", CurSpeed.course_over_ground);)
		RES_( printf( "--------------------------------------------\n");)
	}
}

//-----------------------------------------------------------------//
// Function: GetAntennaStatus()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the status of the
//    gps antenna.
//-----------------------------------------------------------------//
void GetAntennaStatus( void )
{
	int   ReturnCode = 0;

   ReturnCode = GPS_GetStatusAntenna( &AnStatus );
   if( ReturnCode != NO_ERROR )
      RES_( printf( "Error %d in GPS_GetStatusAntenna()...\n", ReturnCode); )
   else {
      RES_( printf( "\n--------------------------------------------\n");)
		switch( AnStatus.A_Status) {
		   case 0:
				RES_( printf ("Antenna status --> STATUS_INIT\n"); )
			break;
			case 1:
				RES_( printf ("Antenna status --> STATUS_DONTKNOW\n"); )
			break;
			case 2:
				RES_( printf ("Antenna status --> STATUS_OK\n"); )
			break;
			case 3:
				RES_( printf ("Antenna status --> STATUS_SHORTCIRCUIT\n"); )
			break;
			case 4:
				RES_( printf ("Antenna status --> STATUS_OPEN\n"); )
			break;
			default:
				RES_( printf ("Antenna status --> VALUE_NOT_VALID\n"); )
			break;
  		}
		switch( AnStatus.A_Power) {
		   case 0:
				RES_( printf ("Antenna power --> POWER_OFF"); )
			break;
		   case 1:
				RES_( printf ("Antenna power --> POWER_ON"); )
			break;
		   case 2:
				RES_( printf ("Antenna power --> POWER_DONTKNOW"); )
			break;
      }
      RES_( printf( "\n--------------------------------------------\n");)
   }
}

//-----------------------------------------------------------------//
// Function: GetStatusJamming()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the status of the
//    jamming state
//-----------------------------------------------------------------//
void GetStatusJamming( void )
{
   int   ReturnCode = 0;
   char  JammingStatus;
	
   ReturnCode = GPS_GetStatusJamming( &JammingStatus );
   if( ReturnCode != NO_ERROR )
      RES_( printf( "Error %d in GPS_GetStatusJamming()...\n", ReturnCode); )
   else {
      RES_( printf( "\n--------------------------------------------\n");)
      RES_( printf( "JammingStatus %x", JammingStatus);)
      RES_( printf( "\n--------------------------------------------\n");)
   }
}

//-----------------------------------------------------------------//
// Function: GetSwVersion()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the gps firmware version.
//-----------------------------------------------------------------//
void GetSwVersion( void )
{
	int   ReturnCode = 0;
   char  binMsg[BINARY_MESSAGE_LENGTH]={0};

   ReturnCode = GPS_Get_Software_Version( binMsg);
   if( ReturnCode != NO_ERROR )
      RES_( printf( "Error %d in GPS_Get_Software_Version()...\n", ReturnCode);)
   else
      RES_( printf("\nOWASYS TEST ---> %s\n", binMsg);)
}

//-----------------------------------------------------------------//
// Function: GetUTCDateTime()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the UTC time and date.
//-----------------------------------------------------------------//
void GetUTCDateTime( void )
{
	int   ReturnCode = 0;

   ReturnCode = GPS_GetUTCDateTime( &CurDateTime );
   if( ReturnCode != NO_ERROR )
      RES_( printf( "Error %d in GPS_GetUTCDateTime()...\n", ReturnCode);)
   else {
      RES_( printf( "\n--------------------------------------------\n");)
      RES_( printf ("HOURS = %hhu\n", CurDateTime.Hours ); )
      RES_( printf ("MINUTES = %hhu\n", CurDateTime.Minutes ); )
      RES_( printf ("SECONDS = %02.02f\n", CurDateTime.Seconds ); )
      RES_( printf ("DAY = %hhu\n", CurDateTime.Day ); )
      RES_( printf ("MONTH = %hhu\n", CurDateTime.Month ); )
      RES_( printf ("YEAR = %d\n", CurDateTime.Year ); )
      RES_( printf( "--------------------------------------------\n");)
   }
}

//-----------------------------------------------------------------//
// Function: GetDOP_FixMode()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the Dilution Of Precision
//    values and also the fix mode.
//-----------------------------------------------------------------//
void GetDOP_FixMode( void )
{
	int           ReturnCode = 0;
   tGNSS_DOP_SV  data;

   ReturnCode = GPS_GetDOP_FixMode( &data );
   if( ReturnCode != NO_ERROR )
      RES_( printf( "Error %d in GPS_GetDOP_FixMode()...\n", ReturnCode);)
   else {
      RES_( printf( "\n--------------------------------------------\n");)
      RES_( printf ("Fix Mode = %hhu\n", data.PosFixMode ); )
      RES_( printf ("TDOP = %02.02f\n", data.TDOP ); )
      RES_( printf ("HDOP = %02.02f\n", data.HDOP ); )
      RES_( printf ("VDOP = %02.02f\n", data.VDOP ); )
      RES_( printf( "--------------------------------------------\n");)
   }
}

//-----------------------------------------------------------------//
// Function: GetSV_inView()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the parameters
//    corresponding to the satellites in view.
//-----------------------------------------------------------------//
void GetSV_inView( void )
{
	int       ReturnCode = 0;
   int       i;

   ReturnCode = GPS_GetSV_inView( &GsvData );
	if( ReturnCode != NO_ERROR )
		RES_( printf( "Error %d in GPS_GetSV_inView()...\n", ReturnCode);)
	else {
		RES_( printf( "\n--------------------------------------------\n");)
  	   RES_( printf ("SVs in view = %hhu\n", GsvData.SV_InView ); )
      for (i=0; i < GsvData.SV_InView; i++) {
	      RES_( printf ("SV_%hhu elevation = %hhu\n", GsvData.SV[i].SV_Id, GsvData.SV[i].SV_Elevation ); )
			RES_( printf ("SV_%hhu azimuth = %hi\n", GsvData.SV[i].SV_Id, GsvData.SV[i].SV_Azimuth ); )
			RES_( printf ("SV_%hhu SNR = %c\n", GsvData.SV[i].SV_Id, GsvData.SV[i].SV_SNR ); )
			RES_( printf ("\n"); )
      }
      RES_( printf( "--------------------------------------------\n");)
   }
}

//-----------------------------------------------------------------//
// Function: GetECEFCoordinates()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the ECEF coordinates.
//-----------------------------------------------------------------//
void GetECEFCoordinates( void )
{
	int ReturnCode = 0;

   ReturnCode = GPS_GetECEF_Coordinates(&ECEFCoord);
   if( ReturnCode != NO_ERROR )
	   RES_( printf( "Error %d in GPS_GetECEF_Coordinates()...\n", ReturnCode);)
   else {
      RES_( printf( "\n-------------------------------------------------------\n");)
            printf("\nOWASYS TEST ---> ECEFCoord.Px=%d\n", ECEFCoord.Px);
            printf("OWASYS TEST ---> ECEFCoord.Py=%d\n", ECEFCoord.Py);
            printf("OWASYS TEST ---> ECEFCoord.Pz=%d\n", ECEFCoord.Pz);
            printf("OWASYS TEST ---> ECEFCoord.Vx=%d\n", ECEFCoord.Vx);
            printf("OWASYS TEST ---> ECEFCoord.Vy=%d\n", ECEFCoord.Vy);
            printf("OWASYS TEST ---> ECEFCoord.Vz=%d\n", ECEFCoord.Vz);
      RES_( printf( "-------------------------------------------------------\n");)
   }
}

//-----------------------------------------------------------------//
// Function: GetGeodeticCoordinates()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the Geodetic coordinates.
//-----------------------------------------------------------------//
void GetGeodeticCoordinates( void )
{
	int ReturnCode = 0;

   ReturnCode = GPS_GetGeodetic_Coordinates(&GeoCoord);
   if( ReturnCode != NO_ERROR )
	   RES_( printf( "Error %d in GPS_GetGeodetic_Coordinates()...\n", ReturnCode);)
   else {
		RES_( printf( "\n-------------------------------------------------------\n");)
      RES_( printf ("LATITUDE  --> %02hu degrees %02hhu minutes %04.04f seconds %c\n",
							GeoCoord.Latitude.Degrees, GeoCoord.Latitude.Minutes,
		   				GeoCoord.Latitude.Seconds, GeoCoord.Latitude.Dir); )
		RES_( printf ("LONGITUDE --> %03hu degrees %02hhu minutes %04.04f seconds %c\n",
							GeoCoord.Longitude.Degrees, GeoCoord.Longitude.Minutes,
							GeoCoord.Longitude.Seconds, GeoCoord.Longitude.Dir); )
		RES_( printf ("ALTITUDE --> %04.04f meters\n", GeoCoord.Altitude); )
		RES_( printf ("NAV STATUS --> %s\n", GeoCoord.NavStatus); )
		RES_( printf( "-------------------------------------------------------\n");)
   }
}

//-----------------------------------------------------------------//
// Function: SetAdquisitionMode()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to set the gps adquisition mode.
//-----------------------------------------------------------------//
void SetAdquisitionMode( void )
{
	int  ReturnCode = 0;
   char gpsmode;
   char strEntry[255];

   printf( "GPS mode (0=normal,1=fast,2=high) >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
	gpsmode = atoi( strEntry);
	if( (ReturnCode = GPS_SetGpsMode(gpsmode)) != NO_ERROR){
	   RES_( printf( "Error %d in GPS_SetGpsMode()...\n", ReturnCode);)
   } else {
      RES_( printf( "GPS_SetGpsMode() OK\n");)
   }
}

//-----------------------------------------------------------------//
// Function: SetDynamicModel()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to set the gps dynamic mode.
//-----------------------------------------------------------------//
void SetDynamicModel( void )
{
	int  ReturnCode = 0;
   char DynamicModel;
   char strEntry[255];

   printf( "Dynamic Model (1-7) >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
	DynamicModel = atoi( strEntry);
	if( (ReturnCode = GPS_SetDynamicModel(DynamicModel)) != NO_ERROR){
      RES_( printf( "Error %d in GPS_SetDynamicModel()...\n", ReturnCode);)
   } else {
      RES_( printf( "GPS_SetDynamicModel() OK\n");)
   }
}

//-----------------------------------------------------------------//
// Function: SetStaticThreshold()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to set the static threshold.
//-----------------------------------------------------------------//
void SetStaticThreshold( void )
{
	int  ReturnCode = 0;
   unsigned char staticThres;
   char strEntry[255];

   printf( "Static Threshold >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
   staticThres = atoi( strEntry);
   if( (ReturnCode = GPS_SetStaticThreshold(staticThres)) != NO_ERROR){
      RES_( printf( "Error %d in GPS_SetStaticThreshold()...\n", ReturnCode);)
   } else{
      RES_( printf( "GPS_SetStaticThreshold() OK\n");)
   }
}

//-----------------------------------------------------------------//
// Function: EnableITFMMode()
// Input Params:  -
// Output Params: -
// Description:
//-----------------------------------------------------------------//
void EnableITFMMode( void )
{
   int  ReturnCode = 0;
   char  strEntry[255];
   char mode;
   char bbt;
   char cwt;
   
   printf( "Mode (1:Enable 0:Disable) >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
   mode = atoi( strEntry);
	
   printf( "Broadband Threshold in dB (0 - 15) >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
   bbt = atoi( strEntry);

   printf( "Continous Wave Threshold in dB (0 - 31) >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
   cwt = atoi( strEntry);
   
   ReturnCode = GPS_Configure_ITFM( mode, bbt, cwt);
   if( ReturnCode != NO_ERROR ){
	   RES_( printf( "Error %d in GPS_Configure_ITFM()...\n", ReturnCode);)
   }
   else {
   }
}

//-----------------------------------------------------------------//
// Function: SendDGPSMsg()
// Input Params:  -
// Output Params: -
// Description:
//-----------------------------------------------------------------//
void SendDGPSMsg( void )
{
	int  ReturnCode = 0;
   char Buffer[]={0};

   ReturnCode = GPS_Send_DGPS_Message(Buffer,1);
   if( ReturnCode != NO_ERROR ){
	   RES_( printf( "Error %d in GPS_Send_DGPS_Message()...\n", ReturnCode);)
   } else {
	   RES_( printf( "GPS_Send_DGPS_Message() OK\n");)
   }
}


//-----------------------------------------------------------------//
// Function: GetNAVConfiguration()
// Input Params:  -
// Output Params: -
// Description:
//-----------------------------------------------------------------//
void GetNAVConfiguration( void )
{
	int   ReturnCode = 0, j, MsgLen;
   char Buffer[256];
   int  i;

   memset(Buffer, 0, 256);
   ReturnCode = GPS_GetCFG_NAV(Buffer, &MsgLen);
   if( ReturnCode != NO_ERROR )
	   printf( "Error %d in GPS_GetCFG_NAV()...\n", ReturnCode);
   else {
      j=0;
      i=0;
      printf("\n");
      do {
         printf("[%02d]", *(Buffer+i));
         i++;
         if (++j == 20) {
            printf("\n");
            j=0;
         }
      }while(i < MsgLen);
      printf("\n");
   }
}

//-----------------------------------------------------------------//
// Function: SetNAVConfiguration()
// Input Params:  -
// Output Params: -
// Description:
//-----------------------------------------------------------------//
void SetNAVConfiguration( void )
{
	int   ReturnCode = 0;
   unsigned char  minsv=0, minele=0;
   short int pdop=0;
   char  strEntry[255];

   printf( "MinSV >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
	minsv = atoi( strEntry);
   printf( "MinEle >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
	minele = atoi( strEntry);
   printf( "PDOP >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
	pdop = atoi( strEntry);

	if( (ReturnCode = GPS_SetNavigationConfig(minsv,minele,pdop)) != NO_ERROR){
	   RES_( printf( "Error %d in GPS_SetNavigationConfig()...\n", ReturnCode);)
   } else{
      RES_( printf( "GPS_SetNavigationConfig() OK\n");)
   }
}

//-----------------------------------------------------------------//
// Function: SetFixConfiguration()
// Input Params:  -
// Output Params: -
// Description:
//-----------------------------------------------------------------//
void SetFixConfiguration( void )
{
	int ReturnCode = 0;
   short int mask;
   unsigned int h_accu;
   char  strEntry[255];

   printf( "Fix Mask >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
	mask = (short int)strtol( strEntry, NULL, 0);
   printf( "Horizontal Accuracy >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
	h_accu = atoi( strEntry);

	if( (ReturnCode = GPS_SetFixConfig( mask, h_accu)) != NO_ERROR){
	   RES_( printf( "Error %d in GPS_SetFixConfig()...\n", ReturnCode);)
   } else{
      RES_( printf( "GPS_SetFixConfig() OK\n");)
   }
}

//-----------------------------------------------------------------//
// Function: GetFixConfiguration()
// Input Params:  -
// Output Params: -
// Description:
//-----------------------------------------------------------------//
void GetFixConfiguration( void )
{
	int ReturnCode = 0;
   short int mask;
   unsigned int h_accu;

	if( (ReturnCode = GPS_GetFixConfig( &mask, &h_accu)) != NO_ERROR){
	   RES_( printf( "Error %d in GPS_GetFixConfig()...\n", ReturnCode);)
   }
   else {
      RES_( printf( "Fix Mask(0x%x), HAccu(%d) OK\n", mask, h_accu);)
   }
}

// Function: GetNavx5()
// Input Params:  -
// Output Params: -
// Description: Get present NAVX5 configuration
//-----------------------------------------------------------------//
void GetNavx5( void )
{
   int ReturnCode;
   int i,j;
   int MsgLen;
   char Navx5Conf[256];

   memset (Navx5Conf, 0, 256); 
   if( (ReturnCode = GPS_GetNAVX5_Data(Navx5Conf, &MsgLen)) != NO_ERROR){
      RES_( printf( "Error %d in GetNavx5()...\n", ReturnCode);)
   } else {
      RES_( printf( "\n--------------------------------------------\n");)
      j=0;
      i=0;
      do {
         printf("[%02d]", *(Navx5Conf+i));
         i++;
         if (++j == 20) {
            printf("\n");
            j=0;
         }
      }while(i < MsgLen);        
      RES_( printf( "\n--------------------------------------------\n");)
   }
}

//-----------------------------------------------------------------//
// Function: SetANA()
// Input Params:  -
// Output Params: -
// Description:
//-----------------------------------------------------------------//
void SetANA( void )
{
   int   ReturnCode = 0;
   char  mode = 0;
   char  strEntry[255];

   printf( "Mode (0:disable 1:enable) >> ");
   memset( ( void *) &strEntry, 0, sizeof( strEntry));
   getEntry( strEntry);
   mode = atoi( strEntry);
   if( (ReturnCode = GPS_SetANA(mode)) != NO_ERROR){
      RES_( printf( "Error %d in SetANA()...\n", ReturnCode);)
   } else {
      RES_( printf( "SetANA() OK\n");)
   }
}

void SetMeasRate( void )
{
   int   ReturnCode = 0;
   char  rate = 2;
   if( (ReturnCode = GPS_SetMeasurementRate(rate)) != NO_ERROR) {
      printf( "Error %d in Set Rate()...\n", ReturnCode);
   } else {
      printf( "Set Rate OK\n");
   }
}

void GetMeasRate( void )
{
   int   ReturnCode = 0;
   char rate;

   if( (ReturnCode = GPS_GetMeasurementRate( &rate)) != NO_ERROR) {
      printf( "Error %d in Get Rate()...\n", ReturnCode);
   } else {
      printf( "Get Rate OK, %dHz\n", rate);
   }
}

//-----------------------------------------------------------------//
// Function: Get_NavSol()
// Input Params:  -
// Output Params: -
// Description:
//-----------------------------------------------------------------//
void Get_NavSol(void )
{
   int ReturnCode = 0;
   tNAV_SOL_DATA LocalInfo;

   if( (ReturnCode = GPS_GetNAV_SOL( &LocalInfo )) != NO_ERROR) {
      printf( "Error %d in get NAV SOL...\n", ReturnCode);
   } else {
      printf( "Get NAV SOL OK\n");
      printf("NAV-SOL: OldValue(%hhu)\r\n", LocalInfo.OldValue);
      printf("TimeOfWeek(%.09f), WeekNumber(%hi), gpsFix(%hhu), flags(0x%x)\r\n", LocalInfo.TimeOfWeek, LocalInfo.WeekNumber,
          LocalInfo.gpsFix, LocalInfo.flags);
      printf("ecefX(%.02f), ecefY(%.02f), ecefZ(%.02f), PosAccu(%.02f)\r\n", LocalInfo.ecefX, LocalInfo.ecefY, LocalInfo.ecefZ, LocalInfo.PosAccu);
      printf("ecefVX(%.02f), ecefVY(%.02f), ecefVZ(%.02f), SpeedAccu(%.02f)\r\n", LocalInfo.ecefVX, LocalInfo.ecefVY, LocalInfo.ecefVZ, LocalInfo.SpeedAccu);
      printf("PositionDOP(%d), numSV(%hhu)\r\n", LocalInfo.PositionDOP, LocalInfo.numSV);
   }
}

//-----------------------------------------------------------------//
// Function: GetModel()
// Input Params:  -
// Output Params: -
// Description:
//    Calls to the gps library function to get the gps model
//-----------------------------------------------------------------//
void GetModel( void )
{
	int   ReturnCode = 0;
   char  binMsg[BINARY_MESSAGE_LENGTH]={0};

   ReturnCode = GPS_Get_Model( binMsg);
   if( ReturnCode != NO_ERROR ){
      RES_( printf( "Error %d in GPS_Get_Model()...\n", ReturnCode);)
   } else {
      RES_( printf("\nOWASYS TEST ---> %s\n", binMsg);)
   }  
}

//-----------------------------------------------------------------//
// Function: handleKeys()
// Input Params:
//               buffer with the entered chars.
// Output Params:
//               0 - success
//              -1 - error
// Description:
//    Checks if the entered characters fit with one the possible
//    commands.
//-----------------------------------------------------------------//
int handleKeys( char* buffer )
{
   int   retVal=0, index;

   for (index=0; buffer[index] != '\0'; index++) {
      if (buffer[ index] > '1') {
         buffer[index] = tolower( buffer[index]);
      }
   }
   if( strncmp(buffer, CMD_GET_FULL_POSITION, strlen(CMD_GET_FULL_POSITION)) == 0) {
      GetFullGPSPosition();
   } else if( strncmp(buffer, CMD_GET_POSITION, strlen(CMD_GET_POSITION)) == 0) {
      GetGPSPosition();
   }
   else if( strncmp(buffer, CMD_GET_SPEED, strlen(CMD_GET_SPEED)) == 0) {
      GetGPSSpeed();
   }
   else if( strncmp(buffer, CMD_GET_ANTENNA, strlen(CMD_GET_ANTENNA)) == 0) {
      GetAntennaStatus();
   }
   else if( strncmp(buffer, CMD_GET_JAMMING, strlen(CMD_GET_JAMMING)) == 0) {
      GetStatusJamming();
   }
   else if( strncmp(buffer, CMD_GET_VERSION, strlen(CMD_GET_VERSION)) == 0) {
      GetSwVersion();
   }
   else if( strncmp(buffer, CMD_GET_UTC, strlen(CMD_GET_UTC)) == 0) {
      GetUTCDateTime();
   }
   else if( strncmp(buffer, CMD_GET_DOP, strlen(CMD_GET_DOP)) == 0) {
      GetDOP_FixMode();
   }
   else if( strncmp(buffer, CMD_GET_SV_VIEW, strlen(CMD_GET_SV_VIEW)) == 0) {
      GetSV_inView();
   }
   else if( strncmp(buffer, CMD_GET_ECEF, strlen(CMD_GET_ECEF)) == 0) {
      GetECEFCoordinates();
   }
   else if( strncmp(buffer, CMD_GET_GEODETIC, strlen(CMD_GET_GEODETIC)) == 0) {
      GetGeodeticCoordinates();
   }
   else if( strncmp(buffer, CMD_SET_ADQUISITION_MODE, strlen(CMD_SET_ADQUISITION_MODE)) == 0) {
      SetAdquisitionMode();
   }
   else if( strncmp(buffer, CMD_SET_DYNAMIC_MODEL, strlen(CMD_SET_DYNAMIC_MODEL)) == 0) {
      SetDynamicModel();
   }
   else if( strncmp(buffer, CMD_SET_STATIC_THRESH, strlen(CMD_SET_STATIC_THRESH)) == 0) {
      SetStaticThreshold();
   }
   else if( strncmp(buffer, CMD_GPS_FINALIZE, strlen(CMD_GPS_FINALIZE)) == 0) {
      retVal = EndGPSModule();
   }
   else if( strncmp(buffer, CMD_GPS_START, strlen(CMD_GPS_START)) == 0) {
      retVal = InitGPSModule();
   }
   else if( strncmp(buffer, CMD_SET_ITFM_MODE, strlen(CMD_SET_ITFM_MODE)) == 0) {
      EnableITFMMode();
   }
   else if( strncmp(buffer, CMD_SEND_DGPS, strlen(CMD_SEND_DGPS)) == 0) {
      SendDGPSMsg();
   }
   else if( strncmp(buffer, CMD_GET_NAV_CONFIG, strlen(CMD_GET_NAV_CONFIG)) == 0) {
      GetNAVConfiguration();
   }
   else if( strncmp(buffer, CMD_SET_NAV_CONFIG, strlen(CMD_SET_NAV_CONFIG)) == 0) {
      SetNAVConfiguration();
   }
   else if( strncmp(buffer, CMD_GET_NAVX5, strlen(CMD_GET_NAVX5)) == 0) {
      GetNavx5();
   }
   else if( strncmp(buffer, CMD_SET_ANA, strlen(CMD_SET_ANA)) == 0) {
      SetANA();
   }
   else if( strncmp(buffer, CMD_CFG_FIX, strlen(CMD_CFG_FIX)) == 0) {
      SetFixConfiguration();
   }
   else if( strncmp(buffer, CMD_GET_FIX, strlen(CMD_GET_FIX)) == 0) {
      GetFixConfiguration();
   }
   else if( strncmp(buffer, CMD_GET_MODEL, strlen(CMD_GET_MODEL)) == 0) {
      GetModel();
   }
   else if( strncmp(buffer, CMD_SET_RATE, strlen(CMD_SET_RATE)) == 0) {
      SetMeasRate();
   }
   else if( strncmp(buffer, CMD_GET_RATE, strlen(CMD_GET_RATE)) == 0) {
      GetMeasRate();
   }
   else if( strncmp(buffer, CMD_GET_NAV_SOL, strlen(CMD_GET_NAV_SOL)) == 0) {
      Get_NavSol();
   }
   else if( strncmp(buffer, CMD_GPS_LED, strlen(CMD_GPS_LED)) == 0) {
      SetGpsLed();
   }
   else if( strncmp(buffer, CMD_LIB_VER, strlen(CMD_LIB_VER)) == 0) {
      GetLibVersion();
   }
	if( strncmp(buffer, CMD_QUIT, strlen(CMD_QUIT)) == 0) {
      return -1;
   }
   return retVal;
}


//-----------------------------------------------------------------//
// Function: main()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
int main(int argc, char *argv[])
{
	int  					ReturnCode = 0;

   printf( " OWASYS -> Starting Test_GPS_Module %s (%s, %s)\n", APP_VERSION, __DATE__ , __TIME__);

   if (InitRTUModule() != NO_ERROR)
      exit(EXIT_FAILURE);

   if (InitIOModule() != NO_ERROR)
      exit(EXIT_FAILURE);

   if (InitGPSModule() != NO_ERROR)
      exit(EXIT_FAILURE);
   

   SetGpsLed();
   SetMeasRate();
   while(1) {
      delay(500);
      GetFullGPSPosition();
      
   }


   if( EndGPSModule() != NO_ERROR) {
      WriteLog("Error %d in EndGPSModule()", ReturnCode);
   }

   if( EndRTUModule() != NO_ERROR) {
      WriteLog("Error %d in EndRTUModule()", ReturnCode);
   }

//IOs MUST BE the last to finalize because it closes the ios driver.
   if( EndIOModule() != NO_ERROR) {
      WriteLog("Error %d in EndIOModule()", ReturnCode);
   }

   exit(EXIT_SUCCESS);
}

//-----------------------------------------------------------------//
// Function: CalculateBinaryChecksum()
// Input Params:							
//                buffer with a binary message
//                buffer lenght 											
// Output Params:
//                calculated checksum
// Description:
//    Calculates the checksum of a binary Ublox message.
//-----------------------------------------------------------------//
int CalculateBinaryChecksum( char *Buff, int len )
{
   int   n;
   char  CK_A=0, CK_B=0;

   for (n=0; n < len; n++) {   // Calculate checksum.
		CK_A += *(Buff+n);
		CK_B += CK_A;
	}
	return ((CK_A<<8) | CK_B);
}

//-----------------------------------------------------------------//
// Function: getEntry() 		
// Input Params:									
//               none									
// Output Params:									
//               strEntry: pointer to the read string									
// Description:
//    Reads input characters.
//-----------------------------------------------------------------//
void getEntry( char *strEntry )
{
   char c = 0;
   int  i = 0;
   while( ( c = getchar()) != 0x0a){
      if( c == 0x0FF){
         strEntry [ i] = 0;
         return;
      }
      if( c == 0x08){ //BackSpace
         if( i>0)
            i--;
         else
            i = 0;
      } else
         strEntry[ i++] = c;
   }
   strEntry [ i] = 0;
   if ( strEntry[ i-1] == 0x0a)
      strEntry[ i-1] = 0;
}

//-----------------------------------------------------------------//
// Function: WriteLog() 		
// Input Params:									
// Output Params:									
// Description:
//-----------------------------------------------------------------//
void WriteLog( const char *format, ... )
{
	va_list arg_ptr;
	char    LineBuffer [512];

	// Get the system date/time
	time_t tmNow;
	struct tm *stmNow;

	tmNow = GetCurTime(NULL);
	stmNow = localtime(&tmNow);
	
	// Put the current date/time in front of the logline
	sprintf(LineBuffer, "%04d%02d%02d-%02d%02d%02d  ",
				stmNow->tm_year + 1900, stmNow->tm_mon+1, stmNow->tm_mday,
				stmNow->tm_hour, stmNow->tm_min, stmNow->tm_sec);

	va_start(arg_ptr, format);
	vsprintf(LineBuffer + strlen (LineBuffer), format, arg_ptr);
	va_end(arg_ptr);

	// Ensure newline
	if(!strchr(LineBuffer, '\n')) {
		strcat(LineBuffer, "\n");
	}

#ifdef DEBUG_TRACES
	// Print it on screen, and in logfile (when available)
	printf(LineBuffer);
	if (logfd != NULL) {
		fwrite(LineBuffer, 1, strlen(LineBuffer), logfd);
		fflush(logfd);
	}
#endif
}

//-----------------------------------------------------------------//
// Function: time_t GetCurTime(time_t *p)
// Input Params:																		
//         pointer to time_t, IN/OUT. gets current time
// Returns:
//         time_t: return current time
// Description:
//         Get current time (replacement for time_t time(time_t*)
//-----------------------------------------------------------------//
time_t GetCurTime( time_t *p )
{
	time_t       tmNow;

	if(p) {
		tmNow = time(p);
	}
	else {
		tmNow = time(NULL);
	}
	
	return tmNow;
}

void SetGpsLed( void)
{

   GPS_Set_Led_Mode(0);
   printf(" Set led to GPS mode");
   
}

void GetLibVersion( void)
{
   unsigned char BufAux[ 32];
   int retVal;
   
   retVal = GPS_GetVersion( BufAux);
   if( retVal) {
      printf("ERROR %d getting library version\r\n", retVal);
   } else {
      printf("LIB VERSION: %s\r\n", BufAux);
   }
}
