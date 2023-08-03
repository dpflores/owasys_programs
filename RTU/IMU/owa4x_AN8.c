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

static void MoveIntHandler( move_int_t wMoveState);
static void GetWakeUpreason( void);

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
   
   int            Option;
   THW_TIME_DATE  CurrentTime;
   unsigned long  MainCpuMask = 0, ExpBoardMask = 0;
   StructVersion  SWVersion;
	move_int_t 		MoveValue;


   unsigned char Range = 0, Threshold = 10, Time = 10;


    if( (ReturnCode = RTUControl_Initialize(NULL)) != NO_ERROR) {
      printf("Error %d in RTUControl_Initialize()...\n", ReturnCode);
      return 1;
    }
    if( (ReturnCode = RTUControl_Start()) != NO_ERROR) {
      printf("Error %d in RTUControl_Start()...\n", ReturnCode);
      return 1;
    }
      
   
   ReturnCode = RTU_CfgMovementSensor(Range, Threshold, Time, (void (*)(move_int_t))&MoveIntHandler);
   if( ReturnCode) {
      printf("ERROR %d in config Acelerometer\n", ReturnCode);
   } 

   while (1)
   {
      char AccelType;

      printf("Enter acceleration type (0: filtered, 1: raw):");
      AccelType = (char) GetULValue();

      if( AccelType == 0) {
               ReturnCode = RTU_GetMovementSensor( &MoveValue);
      } else {
               ReturnCode = RTU_GetRawAcceleration( &MoveValue);
      }
      if( ReturnCode) {
         printf("ERROR %d in getting MOVEMENT SENSOR\n", ReturnCode);
      } else {
            printf("Movement Sensor: Scale(");
            if( MoveValue.scale == 0) {
                  printf("+-2g");
            } else if( MoveValue.scale == 1) {
                  printf("+-4g");
            } else if( MoveValue.scale == 2) {
                  printf("+-8g");
            } else {
                  printf("+-16g");
            }
            printf("), X(%.3fg), Y(%.3fg), Z(%.3fg)\r\n", MoveValue.x_axis, MoveValue.y_axis, MoveValue.z_axis);
      }
   }
     

   do
   {           
    printf("\nOption: ");
    Option = (int) GetULValue();
    switch(Option)
    {
	case 1:
            printHelp();
            
            break;
         
          case 2:
            if(RTUGetExtControllerVersion(&SWVersion))
            {
               printf("ERROR Getting version\n");
            }
            else
            {
               printf(" UC Release = %d\n", SWVersion.Release);
               printf(" UC Version = %d\n", SWVersion.Version);
               printf(" UC Subversion = %d\n", SWVersion.SubV);
            }
            break;
         
          case 3:
            if( (ReturnCode = RTUGetHWTime(&CurrentTime)) != NO_ERROR )
            {
               printf("ERROR %d Getting Time\n", ReturnCode);
            }
            else
            {
               printf("\nCurrent Time:\n");
               printf("Time: %02d:%02d:%02d Date: %d-%s-%d\n", CurrentTime.hour, CurrentTime.min, CurrentTime.sec, CurrentTime.day, MonthList[CurrentTime.month], CurrentTime.year);
            }
            break;

         case 4:
            printf("Input hour (0-23): ");
            CurrentTime.hour = (unsigned char) GetULValue();
            printf("Input min (0-59): ");
            CurrentTime.min = (unsigned char) GetULValue();
            printf("Input sec (0-59): ");
            CurrentTime.sec = (unsigned char) GetULValue();
            printf("Input day (1-31): ");
            CurrentTime.day = (unsigned char) GetULValue();
            printf("Input month (1-12): ");
            CurrentTime.month = (unsigned char) GetULValue();
            printf("Input year: ");
            CurrentTime.year = (unsigned int) GetULValue();

            if(RTUSetHWTime(CurrentTime))
            {
               printf("ERROR Setting Time\n");
            }
            break;

         case 5:
            printf("Input Wake Up Alarm Hour (0-23): ");
            CurrentTime.hour = (unsigned char) GetULValue();
            printf("Input Wake Up Alarm min (0-59): ");
            CurrentTime.min = (unsigned char) GetULValue();
            printf("Input Wake Up Alarm sec (0-59): ");
            CurrentTime.sec = (unsigned char) GetULValue();
            printf("Input Wake Up Alarm day (1-31): ");
            CurrentTime.day = (unsigned char) GetULValue();
            printf("Input Wake Up Alarm month (1-12): ");
            CurrentTime.month = (unsigned char) GetULValue();
            printf("Input Wake Up Alarm year: ");
            CurrentTime.year = (unsigned int) GetULValue();

            if( RTUSetWakeUpTime(CurrentTime) )
            {
               printf("ERROR Setting RTC Wake Up Time\n");
            }
            break;

         case 6:
            FillReturnMask(LP_MODE_STANDBY, &MainCpuMask, &ExpBoardMask);
/*            MainCpuMask = 0x1FF89;
            ExpBoardMask = 0;
            printf("MainCpuMask(0x%lx), ExpBoardMask(0x%lx)\r\n", MainCpuMask, ExpBoardMask);*/
            if( (ReturnCode = RTUEnterStandby(MainCpuMask, ExpBoardMask)) != NO_ERROR)
            {
               printf("ERROR %d Going to Standby\n", ReturnCode);
            } else {
               GetWakeUpreason();
            }
         break;

         case 7:
            FillReturnMask(LP_MODE_OFF, &MainCpuMask, &ExpBoardMask);
            if( RTUEnterStop(MainCpuMask, ExpBoardMask) )
            {
               printf("ERROR Going to OFF\n");
            }
         break;

         case 8: // WakeUpReason
         {
            GetWakeUpreason();
         }
         break;

         case 9: // Get Moved
         {
            unsigned char MovedValue=0;
            if( RTUGetMoved(&MovedValue) )
            {
               printf("ERROR Getting Moved\n");
            }
            else
            {
               printf("Moved: %d\n", MovedValue);
            }
         }
         break;

         case 10: // Moved Reset
         {
            if( RTUResetMoved() )
            {
               printf("ERROR Resetting Moved\n");
            }
            else
            {
               printf("Moved Reset\n");
            }
         }
         break;

         case 11: // Battery state
         {
            unsigned char BattState=0;
            if( (ReturnCode = RTUGetBatteryState(&BattState)) != NO_ERROR )
            {
               printf("ERROR %d getting battery state\n", ReturnCode);
            }
            else
            {
               printf("Battery state(%d)\n", BattState);
               switch(BattState) {
                  case 0:
                     printf("Precharge\n");
                     break; 
                  case 1:
                     printf("Charge Complete\n");
                     break; 
                  case 2:
                     printf("Fast Charge\n");
                     break; 
                  case 3:
                     printf("Temperature/Timer/Sleep\n");
                     break;
               }
            }
         }
         break;

         case 13: //Config Acelerometer
			{
            unsigned char Range, Threshold, Time;

            printf("Enter range (0:+-2g, 1:+-4g, 2:+-8g, 3:+-16g):");
            Range = (unsigned char) GetULValue();
            printf("Enter Threshold (0...127), step 0.015(2g), 0.031(4g), 0.062(8g), 0.125(16g):");
            Threshold = (unsigned char) GetULValue();
            printf("Enter Time (0...127), step 10ms:");
            Time = (unsigned char) GetULValue();

            ReturnCode = RTU_CfgMovementSensor( Range, Threshold, Time, (void (*)(move_int_t))&MoveIntHandler);
            if( ReturnCode) {
               printf("ERROR %d in config Acelerometer\n", ReturnCode);
            } 
			}
         break;

         case 14: //Config Movement
			{
            unsigned char Range, Threshold, Time;
            unsigned short int TimeMov, TimeInts;
            CONFIG_MOVEMENT_DETECT LocalMovementCfg;

            printf("Enter range (0:+-2g, 1:+-4g, 2:+-8g, 3:+-16g):");
            Range = (unsigned char) GetULValue();
            printf("Enter Threshold (0...127), step 0.015(2g), 0.031(4g), 0.062(8g), 0.125(16g):");
            Threshold = (unsigned char) GetULValue();
            printf("Enter Time (0...127), step 10ms:");
            Time = (unsigned char) GetULValue();
            printf("Enter Minimun time detecting interrupts (0,2....900):");
            TimeMov = (unsigned short int) GetULValue();
            printf("Enter Max time between interrupts (0,1....300):");
            TimeInts = (unsigned short int) GetULValue();
				LocalMovementCfg.wScale = Range;
				LocalMovementCfg.wLimit = Threshold;
				LocalMovementCfg.wTime = Time;
				LocalMovementCfg.wHandler = MoveIntHandler;
				LocalMovementCfg.wMinTimeMovement = TimeMov;
				LocalMovementCfg.wMaxTimeBetweenInts = TimeInts;

            ReturnCode = RTU_CfgMovementDetection(&LocalMovementCfg);
            if( ReturnCode) {
               printf("ERROR %d in config Movement\n", ReturnCode);
            } 
	  }
			break;

        case 15: //Get Movement Config
        {
            CONFIG_MOVEMENT_DETECT MovementConfig;

            ReturnCode = RTU_GetCfgMovement(&MovementConfig);
            if( ReturnCode) {
               printf("ERROR %d in getting Movement config\n", ReturnCode);
            } else {
		if( MovementConfig.wEnable == 0) {
                    printf("Accelerometer disabled\n");
		} else {
                    printf("Range(%d), Threshold(%d), Time(%d), Total time(%d), Time ints(%d), Handler(%p)(%p)\n", 
                    MovementConfig.wScale , MovementConfig.wLimit , MovementConfig.wTime , MovementConfig.wMinTimeMovement,
                    MovementConfig.wMaxTimeBetweenInts, MovementConfig.wHandler, &MoveIntHandler );
                    }
		}
        }
	break;

        case 16: //Remove MOVE
            ReturnCode = RTU_RemoveMovementSensor();
            if( ReturnCode) {
               printf("ERROR %d in removing MOVE\n", ReturnCode);
            } 

        break;


      

        default:
            if( Option != 0) {
               printf("Option Not supported\n");
            }
            
        break;

      }
   }while(Option != 0);

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

