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
//** Filename:      rtu_module.cpp
//** Owner:         OWASYS
//** Creation date: 01/04/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//*********************************************************************

#define __RTU_MODULE_CPP

//-----------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------//
#include <stdio.h>

//-----------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------//
#include "rtu_module.h"
#include "Test_GPS_Module.h"
#include "owa4x/owerrors.h"

//-----------------------------------------------------------------//
// Function: InitRTUModule()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
int InitRTUModule( void )
{
   int ReturnCode;

   // start RTUControl
	if( ( ReturnCode = RTUControl_Initialize( NULL)) != NO_ERROR) {
      WriteLog("Error %d in RTUControl_Initialize()", ReturnCode);
      return -1;
  	}

	if( ( ReturnCode = RTUControl_Start()) != NO_ERROR) {
      WriteLog("Error %d in RTUControl_Start()", ReturnCode);
      return -1;
  	}
   // WriteLog("RTU-> Module initialized & started", ReturnCode);
   return NO_ERROR;
}

//-----------------------------------------------------------------//
// Function: EndRTUModule()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
int EndRTUModule( void )
{
   RTUControl_Finalize();
   WriteLog("RTU Module finalized");
   return NO_ERROR;
}

