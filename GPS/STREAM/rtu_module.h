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
//** Filename:      rtu_module.h
//** Owner:         OWASYS
//** Creation date: 01/04/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//*********************************************************************

#ifndef __RTU_MODULE_H
   #define __RTU_MODULE_H

   #define LIBRTU       "/lib/libRTU_Module.so"


   #ifdef __RTU_MODULE_CPP
      void  *LibControlHandle = NULL;

      int InitRTUModule( void );
      int EndModRTU( void );

   #else
      extern int InitRTUModule( void );
      extern int EndRTUModule( void );

   #endif

#endif
