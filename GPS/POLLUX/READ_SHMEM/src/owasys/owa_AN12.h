//*********************************************************************
//*************  Copyright (C) 2016        OWASYS  ********************
//*********************************************************************
//**
//** The copyright to the computer programs here in is the property of
//** OWASYS The programs may be used and/or copied only with the
//** written permission from OWASYS or in accordance with the terms and
//** conditions stipulated in the agreement/contract under which the
//** programs have been supplied.
//**
//*********************************************************************
//********************** File information *****************************
//**
//** Description: This is the header file of owa_AN12.c
//**
//** Filename:      owa_AN12.h
//** Creation date: 19/06/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** P1A      19/06/2017 First release                      Owasys
//*********************************************************************

#ifndef __OWA_AN12_H
   #define __OWA_AN12_H

   //-----------------------------------------------------------------//
   //System Includes
   //-----------------------------------------------------------------//
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
   //-----------------------------------------------------------------//
   //User Includes
   //-----------------------------------------------------------------//

   //-----------------------------------------------------------------//
   //Defines
   //-----------------------------------------------------------------//
   #define APP_VERSION     "1.0.0"
   #define streq(a,b)      (strcmp((a),(b))==0)

   //ANSI colors
   #define BLKHB "\e[0;100m"
   #define BLK "\e[0;30m"
   #define REDHB "\e[0;101m"
   #define RED "\e[0;31m"
   #define GRNHB "\e[0;102m"
   #define GRN "\e[0;32m"
   #define YELHB "\e[0;103m"
   #define YEL "\e[0;33m"
   #define BLUHB "\e[0;104m"
   #define BLU "\e[0;34m"
   #define MAGHB "\e[0;105m"
   #define MAG "\e[0;35m"
   #define CYNHB "\e[0;106m"
   #define CYN "\e[0;36m"
   #define WHTHB "\e[0;107m"
   #define WHT "\e[0;37m"
   #define RESET "\e[0m"
   #define WHTB "\e[0;47m" //white background
   #define WHTR "\e[0;97m" //white foreground
   #define WHTBB "\e[1;97m" //white bold foreground

   #ifdef __OWA_AN12_C

      //-----------------------------------------------------------------//
      //Internal Functions prototypes
      //-----------------------------------------------------------------//
		int main( int argc, char *argv[] );

		int shm_read         ( int memkey, char *tag);
      void print_shared_var( sh_val_t *val, int i);
      time_t get_base_time ( void *ptr, int nofdata);

      //-----------------------------------------------------------------//
      //Public variables
      //-----------------------------------------------------------------//
   
      //-----------------------------------------------------------------//
      //Private variables
      //-----------------------------------------------------------------//

   #else
      //-----------------------------------------------------------------//
      //Exported variables
      //-----------------------------------------------------------------//

      //-----------------------------------------------------------------//
      //Exported functions
      //-----------------------------------------------------------------//
   #endif

#endif

