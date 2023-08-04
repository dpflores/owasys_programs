//*********************************************************************
//*************  Copyright (C) 2002        OWASYS  ********************
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
//** Project:       RTUControl (CYA 000_0296)
//** Description:   Module for RTU control
//**
//** Filename:      Test_RTUControl.h
//** Owner:         Owasys
//** Creation date: 26/07/2010
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** P1A      26/07/2010 First release                      owasys
//*********************************************************************

#ifndef __OWA4X_AN8_H
   #define __OWA4X_AN8_H

//-----------------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------------//
#include "owa4x/owcomdefs.h"
#include "owa4x/pm_messages.h"
#include "owa4x/IOs_ModuleDefs.h"
#include "owa4x/RTUControlDefs.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <stdarg.h>

//-----------------------------------------------------------------------//
//Defines
//-----------------------------------------------------------------------//
#define APP_VERSION   "0.0.3"

   #ifdef __OWA4X_AN8_C
      void getEntry( unsigned char* strEntry);
      void WriteLog( const char *format, ... );
      time_t GetCurTime( time_t *p );
      static int FillReturnMask(unsigned int PowerMode, unsigned long *pMainMask, unsigned long *pExpMask);
      void printHelp( void );

   #else
      extern void WriteLog( const char *format, ... );

   #endif

#endif



