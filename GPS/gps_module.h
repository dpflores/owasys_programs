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
//** Filename:      gps_module.h
//** Owner:         OWASYS
//** Creation date: 01/04/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//*********************************************************************

#ifndef __GPS_MODULE_H
   #define __GPS_MODULE_H

   #define LIBGPS       "/lib/libGPS2_Module.so"

   #ifdef __GPS_MODULE_CPP
      void *LibGPSHandle = NULL;
      BOOL InitGpsFirstTime = TRUE;
      BOOL FinalizeApplication=FALSE;

      int InitGPSModule( void );
      int EndGPSModule( void );

   #else
      // Exported functions & variables
      extern int InitGPSModule( void );
      extern int EndGPSModule( void );
      extern BOOL FinalizeApplication;

   #endif

#endif

