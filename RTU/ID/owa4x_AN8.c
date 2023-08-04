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
//** Project:       RTUControl (CYA 000 0296)
//** Description:   Module for RTU control
//**
//** Filename:      Test_RTUControl.cpp
//** Owner:         Owasys
//** Creation date: 26/07/2010
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** P1A      17/04/2018 First release                      owasys
//*********************************************************************

#define __OWA4X_AN8_C

//-----------------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <memory.h>
#include <time.h>
#include <sys/time.h>
#include "owa4x/owerrors.h"

//-----------------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------------//
#include "owa4x_AN8.h"

//-----------------------------------------------------------------------//
//Defines
//-----------------------------------------------------------------------//

//-----------------------------------------------------------------------//
//Local variables
//-----------------------------------------------------------------------//
static char *MonthList[] = {(char*)"", (char*)"January", (char*)"February", (char*)"March", (char*)"April", (char*)"May", (char*)"Jun", (char*)"July",
                            (char*)"August", (char*)"September", (char*)"October", (char*)"November", (char*)"December"};

//-----------------------------------------------------------------------//
//Local Functions
//-----------------------------------------------------------------------//
static unsigned long GetULValue(void);

void delay(int number_of_seconds);


void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

void getEntry( unsigned char* strEntry)
{
   char c = 0;
   int  i = 0;

   while( ( c = getchar()) != 0x0a) {
      strEntry[ i++] = c;
   }
   strEntry [ i] = 0;
   if ( strEntry[ i-1] == 0x0a)
      strEntry[ i-1] = 0;

}

static void GetWakeUpreason( void)
{
   unsigned long WakeUpReason;
   int ReturnError;
            
   if( (ReturnError = RTUGetWakeUpReason(&WakeUpReason)) != NO_ERROR )
   {
      printf("ERROR %d getting WakeUp Reason\n", ReturnError);
   }
   else
   {
      printf("Wake Up Reason: 0x%lX\n", WakeUpReason);
      if(WakeUpReason & RTU_WKUP_MOVING) printf("Woken by MOVING\n");
      if(WakeUpReason & RTU_WKUP_PWRFAIL) printf("Woken by PWRFAIL\n");
      if(WakeUpReason & RTU_WKUP_RTC) printf("Woken by RTC\n");
      if(WakeUpReason & RTU_WKUP_CONSOLE) printf("Woken by CONSOLE\n");
      if(WakeUpReason & RTU_WKUP_GSM) printf("Woken by GSM\n");
      if(WakeUpReason & RTU_WKUP_DIN0) printf("Woken by DIN0\n");
      if(WakeUpReason & RTU_WKUP_DIN1) printf("Woken by DIN1\n");
      if(WakeUpReason & RTU_WKUP_DIN2) printf("Woken by DIN2\n");
      if(WakeUpReason & RTU_WKUP_DIN3) printf("Woken by DIN3\n");
      if(WakeUpReason & RTU_WKUP_DIN4) printf("Woken by DIN4\n");
      if(WakeUpReason & RTU_WKUP_DIN5) printf("Woken by DIN5\n");
      if(WakeUpReason & RTU_WKUP_DIN6) printf("Woken by DIN6\n");
      if(WakeUpReason & RTU_WKUP_DIN7) printf("Woken by DIN7\n");
      if(WakeUpReason & RTU_WKUP_DIN8) printf("Woken by DIN8\n");
      if(WakeUpReason & RTU_WKUP_DIN9) printf("Woken by DIN9\n");
    }
}

int main( int argc, char *argv[] )
{
   int            ReturnCode   = 0;


    if( (ReturnCode = RTUControl_Initialize(NULL)) != NO_ERROR) {
      printf("Error %d in RTUControl_Initialize()...\n", ReturnCode);
      return 1;
    }
    if( (ReturnCode = RTUControl_Start()) != NO_ERROR) {
      printf("Error %d in RTUControl_Start()...\n", ReturnCode);
      return 1;
    }
      
   
   //Obtener el numero serial del dispositivo
   unsigned char serial;
   if( (ReturnCode = GetSerialNumber(serial)) != NO_ERROR) {
      printf("Error %d in GetSerialNumber()...\n", ReturnCode);
      return 1;
   }
  
   // Print serial number
   printf("Serial Number: %s\n", serial);
   // fflush(stdout);


   if( ( ReturnCode = RTUControl_Finalize()) != NO_ERROR) {
      printf("Error %d in RTUControl_Finalize()...\n", ReturnCode);
      return 1;
   }
   return 0;
}

static void MoveIntHandler( move_int_t wMoveState)
{
   printf("\nowa4x_AN8: Move INTERRUPT\r\nScale(");
	if( wMoveState.scale == 0) {
		printf("+-2g");
	} else if( wMoveState.scale == 1) {
		printf("+-4g");
	} else if( wMoveState.scale == 2) {
		printf("+-8g");
	} else {
		printf("+-16g");
	}
   printf("), X(%.3fg), Y(%.3fg), Z(%.3fg)\r\n", wMoveState.x_axis, wMoveState.y_axis, wMoveState.z_axis);
}

//-----------------------------------------------------------------//
// Function: GetULValue()
// Input Params:									
//    No Params
// Output Params:									
//    Unsigned long value got from input.
// Description:
//    This function gets a string from the input with a number and
//    converts it to an unsigned long.
//
//-----------------------------------------------------------------//
static unsigned long GetULValue(void)
{
   char TempString[256];
   char *EndChar;
   long Answer = 0;
   int i;

   EndChar = TempString;

   i = 0;

   while(EndChar == TempString)
   {
      while((i < 255) && (TempString[i] != '\n'))
      {
         TempString[i] = getchar();

         switch(TempString[i])
         {
            case '\b':
               if(i > 0) i--;
            break;

            case '\n':
            break;

            default:
               i ++;
            break;
         }
      }
      TempString[i] = '\0';

      Answer = (int)strtol(TempString, &EndChar,10);
      if(EndChar == TempString)
      {
         i = 0;
         printf("Please try again.\n");
      }
      else
      {
         break;
      }
   }

   return Answer;
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
	char    LineBuffer[512];

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
	if( !strchr(LineBuffer, '\n') ) {
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

//-----------------------------------------------------------------//
// Function: FillReturnMask()
// Input Params: 									
//    PowerMode (SLEEP, LOW_POWER, ZERO_POWER).
// Output Params:									
//    Mask for waking up with some events.
// Description:
//    This function ask the user for the events for waking up the system
//    and returns the filled mask.
//
//-----------------------------------------------------------------//
static int FillReturnMask(unsigned int PowerMode, unsigned long *pMainMask, unsigned long *pExpMask)
{
   unsigned char  SignalForWakeUp = 0;
   unsigned long ReturnMask = 0x0000;

   switch(PowerMode)
   {
      case LP_MODE_STANDBY:
      printf("MAIN CPU\r\n");
         printf("Wake Up with MOVING signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_MOVING;
         printf("Wake Up with PWRFAIL signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_PWRFAIL;
         printf("Wake Up with RTC signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_RTC;
         printf("Wake Up with CONSOLE signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_CONSOLE;
         printf("Wake Up with GSM signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_GSM;
         printf("Wake Up with CAN1 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_CAN1RD;
         printf("Wake Up with BLE signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_BLE;
         printf("Wake Up with DIN0 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN0;
         printf("Wake Up with DIN1 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN1;
         printf("Wake Up with DIN2 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN2;
         printf("Wake Up with DIN3 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN3;
         printf("Wake Up with DIN4 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN4;
         printf("Wake Up with DIN5 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN5;
         printf("Wake Up with DIN6 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN6;
         printf("Wake Up with DIN7 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN7;
         printf("Wake Up with DIN8 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN8;
         printf("Wake Up with DIN9 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN9;
         *pMainMask = ReturnMask;
         printf("MAIN CPU Wake Up with MASK: 0x%lX\n", *pMainMask);
         break;
      case LP_MODE_OFF:
         printf("MAIN CPU\r\n");
         printf("Wake Up with MOVING signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_MOVING;
         printf("Wake Up with PWRFAIL signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_PWRFAIL;
         printf("Wake Up with RTC signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_RTC;
         printf("Wake Up with CONSOLE signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_CONSOLE;
         printf("Wake Up with DIN0 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN0;
         printf("Wake Up with DIN1 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN1;
         printf("Wake Up with DIN2 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN2;
         printf("Wake Up with DIN3 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN3;
         printf("Wake Up with DIN4 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN4;
         printf("Wake Up with DIN5 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN5;
         printf("Wake Up with DIN6 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN6;
         printf("Wake Up with DIN7 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN7;
         printf("Wake Up with DIN8 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN8;
         printf("Wake Up with DIN9 signal (1-True/0-False): ");
         SignalForWakeUp = (unsigned char)GetULValue();
         if(SignalForWakeUp) ReturnMask |= RTU_WKUP_DIN9;
         *pMainMask = ReturnMask;
         printf("MAIN CPU Wake Up with MASK: 0x%lX\n", *pMainMask);
         break;
      default:
         break;
   }

   return 0;
}

