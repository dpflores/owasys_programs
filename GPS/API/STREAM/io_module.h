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
//** Filename:      io_module.h
//** Owner:         OWASYS
//** Creation date: 01/04/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//*********************************************************************

#ifndef __IO_MODULE_H
   #define __IO_MODULE_H

   #define LIBIO "/lib/libIOs_Module.so"

   #ifdef __IO_MODULE_CPP
      void *LibGPIOHandle = NULL;

      int InitIOModule( void );
      int EndIOModule( void );

   #else
      // Exported functions & variables
      extern int InitIOModule( void );
      extern int EndIOModule( void );

   #endif

#endif

