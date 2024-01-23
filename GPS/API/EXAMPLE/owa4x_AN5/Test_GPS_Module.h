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
//** Filename:      Test_GPS_Module.h
//** Owner:         OWASYS
//** Creation date: 01/04/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//*********************************************************************

#ifndef __Test_GPS_Module_H
   #define __Test_GPS_Module_H

//-----------------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------------//
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#include "owa4x/owcomdefs.h"
#include "owa4x/GPS2_ModuleDefs.h"
#include "owa4x/pm_messages.h"
#include "owa4x/IOs_ModuleDefs.h"
#include "owa4x/RTUControlDefs.h"


//-----------------------------------------------------------------//
//Macros
//-----------------------------------------------------------------//
#ifdef DEBUG_TRACES
   #define DEBUG_(x) x
#endif

typedef int BOOL;

#define RES_(x) x
//   #define RES_(x)   // No printfs...


//-----------------------------------------------------------------------//
//Defines
//-----------------------------------------------------------------------//
#define APP_VERSION   "0.0.3"

//Commands
#define CMD_GET_FULL_POSITION      "get fullpos\0"
#define CMD_GET_POSITION           "get pos\0"
#define CMD_GET_SPEED              "get speed\0"
#define CMD_GET_ANTENNA            "get antenna\0"
#define CMD_GET_JAMMING            "get jamming\0"
#define CMD_GET_DATUM              "get datum\0"
#define CMD_SET_DATUM              "set datum\0"
#define CMD_GET_DATUM_EXTENDED     "get datum ext\0"
#define CMD_SET_DATUM_EXTENDED     "set datum ext\0"
#define CMD_GET_VERSION            "get sw ver\0"
#define CMD_GET_UTC                "get date\0"
#define CMD_GET_DOP                "get dop\0"
#define CMD_GET_SV_VIEW            "get sv view\0"
#define CMD_GET_ECEF               "get ecef\0"
#define CMD_GET_GEODETIC           "get geo\0"
#define CMD_SET_ADQUISITION_MODE   "set adq mode\0"
#define CMD_SET_DYNAMIC_MODEL      "set dynamic\0"
#define CMD_SET_STATIC_THRESH      "set static\0"
#define CMD_GPS_FINALIZE           "gps end\0"
#define CMD_GPS_START              "gps start\0"
#define CMD_SET_ITFM_MODE          "set jamming\0"
#define CMD_SEND_DGPS              "send dgps\0"
#define CMD_GET_NAV_CONFIG         "get nav config\0"
#define CMD_SET_NAV_CONFIG         "set nav config\0"
#define CMD_GET_NAVX5              "get navx5\0"
#define CMD_SET_ANA                "set ana\0"
#define CMD_QUIT                   "quit\0"
#define CMD_CFG_FIX                "set fix\0"
#define CMD_GET_FIX                "get fix\0"
#define CMD_GET_MODEL              "get model\0"
#define CMD_SEND_DGPS              "send dgps\0"
#define CMD_SET_RATE               "set m_rate\0"
#define CMD_GET_RATE               "get m_rate\0"
#define CMD_GET_NAV_SOL            "get nav sol\0"
#define CMD_GPS_LED                "gps led"
#define CMD_LIB_VER                "lib ver"

#define BINARY_MESSAGE_LENGTH      1024


   #ifdef __TEST_GPS_Module_CPP
	// local functions
	   int main(int argc, char *argv[]);
      void getEntry( char* strEntry );
      void WriteLog( const char *format, ... );
      time_t GetCurTime( time_t *p );
      int CalculateBinaryChecksum( char *Buff, int len );
      void WriteToFile( char *FileName, char *Buffer, int len);
      void *SendAIDFilesThread( void *arg );
      void ReadFile( char *filename );
      void InitMQTTConn( void);
      void *RTCM3HandleEvents( void *arg);
      void *KMLFileThread( void *arg);

      void GetFullGPSPosition( void );
      void GetGPSPosition( void );
      void GetGPSSpeed( void );
      void GetAntennaStatus( void );
      void GetSwVersion( void );
      void GetUTCDateTime( void );
      void GetDOP_FixMode( void );
      void GetSV_inView( void );
      void GetECEFCoordinates( void );
      void GetGeodeticCoordinates( void );
      void SetAdquisitionMode( void );
      void SetDynamicModel( void );
      void SetStaticThreshold( void );
      void SetSBASMode( void );
      void ResetSBASMode( void );
      void SendDGPSMsg( void );
      void GetNAVConfiguration( void );
      void SetNAVConfiguration( void );
      void SetFixConfiguration( void );
      void GetFixConfiguration( void );
      void GetModel( void );
      void GetNavRelposned( void );
      void SetMeasRate( void );
      void GetMeasRate( void );
      void Get_NavSvin( void );
      void Get_NavSol( void );
      void SetGpsLed( void );
      void GetLibVersion( void );


	TGPS_POS 		CurCoords;
	TGPS_SPEED		CurSpeed;
	char			TXBuffer[256];
	tANTENNA_NEW_STATUS     AnStatus;
	TUTC_DATE_TIME		CurDateTime;
        tGEODETIC_COORDINATES   GeoCoord;
        TANTENNA_STATUS         AnStatusOld;
        tECEF_COORDINATES       ECEFCoord;
        tDATUM                  Datum;
        tGSV_Data               GsvData;

   #else
      extern void WriteLog( const char *format, ... );

   #endif

#endif

