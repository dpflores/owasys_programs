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
//** Filename:      io_module.cpp
//** Owner:         OWASYS
//** Creation date: 01/04/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//*********************************************************************

#define __IO_MODULE_CPP

//-----------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------//
#include <stdio.h>

//-----------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------//
#include "io_module.h"
#include "Test_GPS_Module.h"
#include "owa4x/owerrors.h"

//-----------------------------------------------------------------//
// Function: InitIOModule()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
int InitIOModule( void )
{
   int                       ReturnCode;
   
  	// configure and start IOsModule
   if( ( ReturnCode = IO_Initialize( )) != NO_ERROR) {
      WriteLog("Error %d in IO_Initialize()", ReturnCode);
     	return -1;
   }
 	if( ( ReturnCode = IO_Start()) != NO_ERROR) {
      WriteLog("Error %d in IO_Start()", ReturnCode);
		IO_Finalize();
		return -1;
   }
   WriteLog("IOs-> Module initialized & started");
   return NO_ERROR;
}

//-----------------------------------------------------------------//
// Function: EndModIO()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
int EndIOModule( void )
{
   IO_Finalize();
   WriteLog("IO->Module finalized");
   return NO_ERROR;
}

