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
//** Filename:      gps_module.cpp
//** Owner:         OWASYS
//** Creation date: 01/04/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//*********************************************************************

#define __GPS_MODULE_CPP

//-----------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------//
#include <stdio.h>
#include <string.h>

//-----------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------//
#include "Test_GPS_Module.h"
#include "gps_module.h"
#include "owa4x/owcomdefs.h"
#include "owa4x/owerrors.h"

//-----------------------------------------------------------------//
// Function: InitGPSModule()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
int InitGPSModule( void )
{
   TGPS_MODULE_CONFIGURATION  GPSConfiguration;
   char                       GpsValidType[][20] = {"NONE", "GPS_UBLOX"};
   char                       GpsValidProtocol[][10] = {"NMEA", "BINARY"};
   int                        ReturnCode, IsActive;

   if (InitGpsFirstTime) {
     // load GPS library and its functions
      InitGpsFirstTime = FALSE;
   }

   memset( &GPSConfiguration, 0, sizeof( TGPS_MODULE_CONFIGURATION));
   strcpy(GPSConfiguration.DeviceReceiverName, GpsValidType[1]);
   GPSConfiguration.ParamBaud = B115200;
   GPSConfiguration.ParamLength = CS8;
   GPSConfiguration.ParamParity = IGNPAR;
   strcpy(GPSConfiguration.ProtocolName, GpsValidProtocol[0]);
   GPSConfiguration.GPSPort = COM1;

  	// GPS module initialization.
  	if( ( ReturnCode = GPS_Initialize( ( void *) &GPSConfiguration)) != NO_ERROR) {
      WriteLog("Error %d in GPS_Initialize()", ReturnCode);
      if (ReturnCode != ERROR_GPS_ALREADY_INITIALIZED) {
     	   return -1;
      }
   }
   // GPS receiver startup
  	if ( ( ReturnCode = GPS_Start()) != NO_ERROR ) { //start GPS receiver.
      WriteLog("Error %d in GPS_Start()", ReturnCode);
      if (ReturnCode != ERROR_GPS_ALREADY_STARTED) {
     	   return -1;
      }
   }
	GPS_IsActive( &IsActive);
	printf("IS ACTIVE(%d)\r\n", IsActive);
   WriteLog("GPS-> Module initialized & started");
   return NO_ERROR;
}

//-----------------------------------------------------------------//
// Function: EndGPSModule()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
int EndGPSModule( void )
{
   int ReturnCode;

   if( ( ReturnCode = GPS_Finalize()) != NO_ERROR ) {
      WriteLog("Error %d in GPS_Finalize()", ReturnCode);
      return -1;
   }

   WriteLog("GPS-> Module finalized");
   return NO_ERROR;
}


