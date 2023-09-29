//*********************************************************************
//*************  Copyright (C) 2017        OWASYS  ********************
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
//** Project:        owa4x_AN3
//** Description:    Module for IOs, Leds, Timers and Interrupts
//**                 management
//**
//** Filename:       owa4x_AN3.cpp
//** Owner:          Owasys
//** Creation date:  15/12/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** V1.0.0   15/12/2017 First release                      owasys
//*********************************************************************

#define __OWA3X_AN3_CPP

//-----------------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <owa4x/pm_messages.h>
#include <owa4x/owerrors.h>


//-----------------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------------//
#include "owa4x_AN3.h"
#include "LoadLibs.h"
#include "uarts.h"
#include "owa4x/IOs_ModuleDefs.h"
//-----------------------------------------------------------------//
// Function: getvalue()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
int getvalue( char *buffer )
{
   char *ptr = NULL;
   int  i=0, j=0;

   for(i=0; buffer[i] != '\0'; i++) {
      if( buffer[i] == ' ' ) {
         j++;
      }
   }

   ptr = buffer;
   do {
      if( (ptr=strchr(ptr, ' ')) == NULL )
         return -1;
      ptr++;
   }while(--j > 0);

   if( strchr(ptr, '0') != NULL )
      return 0;
   if( strchr(ptr, '1') != NULL )
      return 1;
   return -1;
}

//-----------------------------------------------------------------//
// Function: handleKeys()
// Input Params:
//               buffer with the entered chars.
// Output Params:
//               0 - success
//              -1 - error
// Description:
//    Checks if the entered characters fit with one the possible
//    commands.
//-----------------------------------------------------------------//
int handleKeys( char *buffer )
{
   int   retVal=0, index;
   int   value;

   for(index=0; buffer[index] != '\0'; index++) {
      if( buffer[index] > '1' ) {
         buffer[index] = tolower(buffer[index]);
      }
   }

   if( strncmp(buffer, CMD_SET_ADC_RANGE, strlen(CMD_SET_ADC_RANGE)) == 0 ) {
      Set_Adc_Range();
   }
   else if( strncmp(buffer, CMD_SET_LED_SW0, strlen(CMD_SET_LED_SW0)) == 0 ) {
      if( (value = getvalue(buffer)) < 0 )
         return value;
      (*FncDIGIO_Set_LED_SW0)((unsigned char)value);
   }
   else if( strncmp(buffer, CMD_SET_LED_SW1, strlen(CMD_SET_LED_SW1)) == 0 ) {
      if( (value = getvalue(buffer)) < 0 )
         return value;
      (*FncDIGIO_Set_LED_SW1)((unsigned char)value);
   }
   else if( strncmp(buffer, CMD_SET_LED_SW2, strlen(CMD_SET_LED_SW2)) == 0 ) {
      if( (value = getvalue(buffer)) < 0 )
         return value;
      (*FncDIGIO_Set_LED_SW2)((unsigned char)value);
   }
   else if( strncmp(buffer, CMD_SET_LED_SW3, strlen(CMD_SET_LED_SW3)) == 0 ) {
      if( (value = getvalue(buffer)) < 0 )
         return value;
      (*FncDIGIO_Set_PPS_GPS)((unsigned char)value);
   }
   else if( strncmp(buffer, CMD_GET_ANA0, strlen(CMD_GET_ANA0)) == 0 ) {
      retVal = (*FncANAGIO_GetAnalogIn)( 0, &value);
      if( retVal == NO_ERROR ) {
         printf(" ANALOG INPUT 0 = %d\n", value);
      } else {
         printf(" Error %d reading ANALOG INPUT 0\n", retVal);
      }
   }
   else if( strncmp(buffer, CMD_GET_ANA1, strlen(CMD_GET_ANA1)) == 0 ) {
      retVal = (*FncANAGIO_GetAnalogIn)( 1, &value);
      if( retVal == NO_ERROR ) {
         printf(" ANALOG INPUT 1 = %d\n", value);
      } else {
         printf(" Error %d reading ANALOG INPUT 1\n", retVal);
      }
   }
   else if( strncmp(buffer, CMD_GET_ANA2, strlen(CMD_GET_ANA2)) == 0 ) {
      retVal = (*FncANAGIO_GetAnalogIn)( 2, &value);
      if( retVal == NO_ERROR ) {
         printf(" ANALOG INPUT 2 = %d\n", value);
      } else {
         printf(" Error %d reading ANALOG INPUT 2\n", retVal);
      }
   }
   else if( strncmp(buffer, CMD_GET_ANA3, strlen(CMD_GET_ANA3)) == 0 ) {
      retVal = (*FncANAGIO_GetAnalogIn)( 3, &value);
      if( retVal == NO_ERROR ) {
         printf(" ANALOG INPUT 3 = %d\n", value);
      } else {
         printf(" Error %d reading ANALOG INPUT 3\n", retVal);
      }
   }
   else if( strncmp(buffer, CMD_CFG_int, strlen(CMD_CFG_int)) == 0 ) {
      Config_Interrupts();
   }
   else if( strncmp(buffer, CMD_GET_intS, strlen(CMD_GET_intS)) == 0 ) {
      Get_Interrupts();
   }
   else if( strncmp(buffer, CMD_REMOVE_int, strlen(CMD_REMOVE_int)) == 0 ) {
      Remove_Interrupts();
   }
   else if( strncmp(buffer, CMD_GET_IN, strlen(CMD_GET_IN)) == 0 ) {
      Get_Dig_In();
   }
   else if( strncmp(buffer, CMD_GET_ALL_IN, strlen(CMD_GET_ALL_IN)) == 0 ) {
      Get_All_Dig_In();
   }
   else if( strncmp(buffer, CMD_SET_OUT, strlen(CMD_SET_OUT)) == 0 ) {
      Set_Dig_Out();
   }
   else if( strncmp(buffer, CMD_SET_ALL_OUT, strlen(CMD_SET_ALL_OUT)) == 0 ) {
      Set_All_Dig_Out();
   }
   else if( strncmp(buffer, CMD_TEST_TIMER, strlen(CMD_TEST_TIMER)) == 0 ) {
      Test_Timers();
   }
   else if( strncmp(buffer, CMD_ENABLE_485, strlen(CMD_ENABLE_485)) == 0 ) {
      Enable_RS485();
   }
   else if( strncmp(buffer, CMD_RX_485, strlen(CMD_RX_485)) == 0 ) {
      Rx_RS485(1);
   }
   else if( strncmp(buffer, CMD_TX_485, strlen(CMD_TX_485)) == 0 ) {
      Tx_RS485();
   }
   else if( strncmp(buffer, CMD_ENABLE_KLINE, strlen(CMD_ENABLE_KLINE)) == 0 ) {
      Enable_KLine();
   }
   else if( strncmp(buffer, CMD_TEST_UART1, strlen(CMD_TEST_UART1)) == 0 ) {
      Test_Uart1();
   }
   else if( strncmp(buffer, CMD_ENABLE_UART5, strlen(CMD_ENABLE_UART5)) == 0 ) {
      Enable_Uart5();
   }
   else if( strncmp(buffer, CMD_TEST_UART5, strlen(CMD_TEST_UART5)) == 0 ) {
      Test_Uart5();
   }
   else if( strncmp(buffer, CMD_SET_SD, strlen(CMD_SET_SD)) == 0 ) {
      Set_SD_Card();
   }
   else if( strncmp(buffer, CMD_GET_USB_A, strlen(CMD_GET_USB_A)) == 0 ) {
      Get_USB_A();
   }
   else if( strncmp(buffer, CMD_GET_VIN, strlen(CMD_GET_VIN)) == 0 ) {
      GetVin();
   }
   else if( strncmp(buffer, CMD_GET_VBAT, strlen(CMD_GET_VBAT)) == 0 ) {
      GetVbat();
   }
   else if( strncmp(buffer, CMD_GET_TEMP, strlen(CMD_GET_TEMP)) == 0 ) {
      GetTemp();
   }
   else if( strncmp(buffer, CMD_ENABLE_IBUTTON, strlen(CMD_ENABLE_IBUTTON)) == 0 ) {
      if((*FncIBUTTON_CfgInt)(iButtonInterruptHandler) != 0) {
         printf("iButton Interrupt handler NOT set\n");
      }
      else {
         printf("iButton Interrupt handler set\n");
      }
   }
   else if( strncmp(buffer, CMD_DISABLE_IBUTTON, strlen(CMD_DISABLE_IBUTTON)) == 0 ) {
      if((*FncIBUTTON_RemoveInt)() != 0) {
         printf("iButton Interrupt handler NOT removed\n");
      }
      else {
         printf("iButton Interrupt handler removed\n");
      }
   }
   else if( strncmp(buffer, CMD_READ_OWTEMP, strlen(CMD_READ_OWTEMP)) == 0 ) {
      unsigned char Id[IB_ID_LENGTH];
      int i, analogValue;
      unsigned char iButtonTempMem [ IBUTTON_DS1820_MEMSIZE];
      unsigned char iB, iTemp;

      printf("Read iButton ID\n");
      // Detect temp sensor ID to know the type of sensor from byte 0
      if((*FncIBUTTON_ReadID)(Id) != 0) {
         printf("sensor not detected\n");
      }

      if ((retVal = (*FncIBUTTON_Reset) ()) == NO_ERROR) {
         (*FncIBUTTON_WriteByte) (IBUTTON_SKIP_ROM);
         (*FncIBUTTON_WriteByte) (IBUTTON_CONVERT_T);
         (*Fncusecsleep)(0, 750000);
         (*FncIBUTTON_Reset)();
         (*FncIBUTTON_WriteByte) (IBUTTON_SKIP_ROM);
         (*FncIBUTTON_WriteByte) (IBUTTON_READ_MEM);
         memset(iButtonTempMem, 0xFF, IBUTTON_DS1820_MEMSIZE);
         for (i = 0; i < IBUTTON_DS1820_MEMSIZE; i++) {
            retVal = (*FncIBUTTON_ReadByte)(&iB);
            if ((retVal == NO_ERROR) || (retVal == 0xFF)) {
               //printf( "byte %d -> %02x\n", i, iB);
               iButtonTempMem[i] = iB;
            }
         }
         switch (Id[0]){
            case DS18S20:
               printf("Temp sensor DS18S20\n");
               if (iButtonTempMem[1] & 0x80) {
                  iTemp = iButtonTempMem[0] ^ 0xFF;
                  iTemp += 1;
                  printf("Temp: %4.2f\n", ((float)iTemp) / 2);
               } else {
                  printf("Temp: %4.2f\n", ((float) iButtonTempMem[0]) / 2);
               }
               break;
            case DS1822:
            case DS18B20:
               printf("Temp sensor DS18B20\n");
               analogValue = 0;
               analogValue = ((int)iButtonTempMem[1]) << 8;
               analogValue += iButtonTempMem[0];
               if( analogValue > 0x8000){ //Check sign
                  analogValue = (-1) * ( analogValue ^ 0xFFFF);
               }
               printf( "temp: %4.2f\n", ((float) analogValue) / 16.0);
               break;
            default:
               printf("Temp sensor not valid\n");
               return -1;
         }
      } else {
         printf("error sending one wire reset\n");
      }
   }
   else if( strncmp(buffer, CMD_READ_IBUTTON, strlen(CMD_READ_IBUTTON)) == 0 ) {
      unsigned char Value[IB_ID_LENGTH];
      int i;

      printf("Read iButton ID\n");
      // Detect iButton
      if((*FncIBUTTON_ReadID)(Value) != 0) {
         printf("iButton Not Detected\n");
      }
      else {
         printf("iButton detected\n");
         printf("ID: ");
         for(i = 0; i < IB_ID_LENGTH; i ++)
         {
            printf("0x%hhX ", Value[i]);
         }
         printf("\n");
      }
   }
   else if( strncmp(buffer, CMD_SET_VOUT, strlen(CMD_SET_VOUT)) == 0 ) {
      Set_VOUT();
   }
   else if( strncmp(buffer, CMD_GET_VOUT, strlen(CMD_GET_VOUT)) == 0 ) {
      Get_VOUT_STATUS();
   }
   else if( strncmp(buffer, CMD_GET_PWR_FAIL, strlen(CMD_GET_PWR_FAIL)) == 0 ) {
      Get_PWR_FAIL();
   }
   else if( strncmp(buffer, CMD_ENABLE_CAN, strlen(CMD_ENABLE_CAN)) == 0 ) {
      EnableCan();
   }
   else if( strncmp(buffer, CMD_DIS_OW, strlen(CMD_DIS_OW)) == 0 ) {
      DiscoverOneWire();
   }
   else if( strncmp(buffer, CMD_UPDATE_OW, strlen(CMD_UPDATE_OW)) == 0 ) {
      UpdateOneWire();
   }
   else if( strncmp(buffer, CMD_RESET_OW, strlen(CMD_RESET_OW)) == 0 ) {
      ResetUpdateOneWire();
   }
   else if( strncmp(buffer, CMD_CAN1TX_MODE, strlen(CMD_CAN1TX_MODE)) == 0 ) {
      Set_CAN_TX_Mode(1);
   }
   else if( strncmp(buffer, CMD_CAN2TX_MODE, strlen(CMD_CAN2TX_MODE)) == 0 ) {
      Set_CAN_TX_Mode(2);
   }
   else if( strncmp(buffer, CMD_CAN3TX_MODE, strlen(CMD_CAN3TX_MODE)) == 0 ) {
      Set_CAN_TX_Mode(3);
   }
   else if( strncmp(buffer, CMD_CAN4TX_MODE, strlen(CMD_CAN4TX_MODE)) == 0 ) {
      Set_CAN_TX_Mode(4);
   }
   else if( strncmp(buffer, CMD_SWITCH_GPS, strlen(CMD_SWITCH_GPS)) == 0 ) {
      Switch_GPS();
   }
   else if( strncmp(buffer, CMD_KLINE1_TH, strlen(CMD_KLINE1_TH)) == 0 ) {
      Set_KLINE1_Threshold();
   }
   else if( strncmp(buffer, CMD_KLINE2_TH, strlen(CMD_KLINE2_TH)) == 0 ) {
      Set_KLINE2_Threshold();
   }
   else if( strncmp(buffer, CMD_BAT_STAT, strlen(CMD_BAT_STAT)) == 0 ) {
      Get_Bat_Stat();
   }
   else if( strncmp(buffer, CMD_GET_BAT_CH, strlen(CMD_GET_BAT_CH )) == 0 ) {
      Get_Bat_Charge_Stat();
   }
   else if( strncmp(buffer, CMD_SET_BAT_CH, strlen(CMD_SET_BAT_CH)) == 0 ) {
      Set_Bat_Charge_Stat();
   }
   else if( strncmp(buffer, CMD_QUIT, strlen(CMD_QUIT)) == 0 ) {
      return -1;
   }
   else {
      printf("Unknown(%s) command\r\n", buffer);
   }
   return 0;
}

//-----------------------------------------------------------------//
// Function: printHelp()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
void printHelp( void )
{
   printf("\n");
   printf("------------------------------------------------------------------------------\n");
   printf("| get input      | test uart1       | get vbat            | discover ow      |\n");
   printf("| get all input  | test uart5       | get temp            | update ow        |\n");
   printf("| cfg int        | set out          | set sd              | read ibutton     |\n");
   printf("| get ints       | set all out      | enable 485          | reset ow         |\n");
   printf("| rem int        | set greenled     | rx 485              | set vout         |\n");
   printf("| set adc_range  | set redled       | tx 485              | get vout         |\n");
   printf("| get ana0       | set yellowled    | enable kline        | get pwr_fail     |\n");
   printf("| get ana1       | set orangeled    | enable uart5        | enable can       |\n");
   printf("| get ana2       | get usb_a        | enable ibutton      | test timer       |\n");
   printf("| get ana3       | get vin          | disable ibutton     | switch gps       |\n");
   printf("| kline2 th      | kline1 th        | can1tx mode         | can2tx mode      |\n");
   printf("| can3tx mode    | can4tx mode      | read owtemp         |                  |\n");
   printf("| get bat-stat   | get bat-charge   | set bat-charge      | quit             |\n");
   printf("------------------------------------------------------------------------------\n");
}

//-----------------------------------------------------------------//
// Function: getEntry()
// Input Params:
//               none
// Output Params:
//               strEntry: pointer to the read string
// Description:
//    Reads input characters.
//-----------------------------------------------------------------//
void getEntry( char *strEntry )
{
   char c = 0;
   int  i = 0;

   while( (c = getchar()) != 0x0a) {
      if( c == 0x0FF ) {
         strEntry [ i] = 0;
         return;
      }
      if( c == 0x08 ) { //BackSpace
         if( i>0)
            i--;
         else
            i = 0;
      } else
         strEntry[i++] = c;
   }
   strEntry[i] = 0;
   if( strEntry[i-1] == 0x0a )
      strEntry[i-1] = 0;
}


int main( void )
{
   int   ReturnCode = 0;
   void  *LibIOHandle = NULL;
   void  *LibRTUControlHandle = NULL;


	printf("Enter owa3x_AN3 version(%s) program\r\n", SW_VERSION);
   LoadExternalLibrary((char *)LIBRTU, &LibRTUControlHandle);
   LoadRTUControlFunctions( LibRTUControlHandle);
	printf("All external Control functions loaded\n");

  	LoadExternalLibrary((char *)LIBIO, &LibIOHandle);
   LoadIOSFunctions(LibIOHandle);

   printf("All external functions loaded...\n");
   if( (ReturnCode = (*FncRTUControl_Initialize)(NULL)) != NO_ERROR) {
      printf("Error %d in RTUControl_Initialize()...\n", ReturnCode);
      UnloadExternalLibrary(LibRTUControlHandle);
      UnloadExternalLibrary(LibIOHandle);
      return 1;
   }
   if( (ReturnCode = (*FncRTUControl_Start)()) != NO_ERROR) {
      printf("Error %d in RTUControl_Start()...\n", ReturnCode);
      UnloadExternalLibrary(LibRTUControlHandle);
      UnloadExternalLibrary(LibIOHandle);
      return 1;
   }
   if( (ReturnCode = (*FncIO_Initialize)() ) != NO_ERROR ) {
      printf("Error %d in IO_Initialize()...\n", ReturnCode);
      UnloadExternalLibrary(LibRTUControlHandle);
      UnloadExternalLibrary(LibIOHandle);
      return 1;
   }
   if( (ReturnCode = (*FncIO_Start)()) != NO_ERROR ) {
      printf("Error %d in IO_Start()...\n", ReturnCode);
      UnloadExternalLibrary(LibRTUControlHandle);
      UnloadExternalLibrary(LibIOHandle);
      return 1;
   }

   GetVbat();


   if( (ReturnCode = (*FncIO_Finalize)()) != NO_ERROR ) {
      printf( "Error %d in IO_Finalize()...\n", ReturnCode);
   }
   if( ( ReturnCode = (*FncRTUControl_Finalize)()) != NO_ERROR) {
      printf("Error %d in RTUControl_Finalize()...\n", ReturnCode);
   }
   UnloadExternalLibrary(LibRTUControlHandle);
   UnloadExternalLibrary(LibIOHandle);
   return 0;
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

	// Print it on screen, and in logfile (when available)
	printf(LineBuffer);
#ifdef DEBUG_TRACES
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

static int Get_Dig_In( void)
{
   int value, retVal;
   unsigned char  readvalue;
   char  BufKey[16];

   printf("Enter INPUT number (0..9):");
   getEntry(BufKey);
   value = atoi(BufKey);
   retVal = (*FncDIGIO_Get_DIN)( value, &readvalue);
   if( retVal == NO_ERROR ) {
      printf(" IN%d = %hhu", value, readvalue);
   } else {
      printf("Error %d getting Input %d\r\n", retVal, value);
   }
   return retVal;
}

static int Get_All_Dig_In( void)
{
   int retVal;
   unsigned short int readvalue;
   unsigned char  read;

   retVal = (*FncDIGIO_Get_All_DIN)( &readvalue);
   if( retVal == NO_ERROR ) {
      printf(" INPUTS = 0x%hx\n", readvalue);
     
      for(int i=0;i<10;i++){
      retVal = (*FncDIGIO_Get_DIN)( i, &read);
        if( retVal == NO_ERROR ) {
          printf(" IN%d = %hhu\n", i, read);
        } else {
          printf("Error %d getting Input %d\r\n", retVal, i);
        }
       }
   } else {
      printf("Error %d getting All Inputs\r\n", retVal);
   }
   return retVal;
}

static int Set_Dig_Out( void)
{
   int value, retVal;
   unsigned char  readvalue;
   char  BufKey[16];

   printf("Enter OUTPUT number (0..9):");
   getEntry(BufKey);
   value = atoi(BufKey);
   printf("Enter OUTPUT value (0..1):");
   getEntry(BufKey);
   readvalue = atoi(BufKey);
   retVal = (*FncDIGIO_Set_DOUT)( value, readvalue);
   if( retVal == NO_ERROR ) {
      printf(" OUT%d = %hhu", value, readvalue);
   } else {
      printf("Error %d setting Output %d\r\n", retVal, value);
   }
   return retVal;
}

static int Set_All_Dig_Out( void)
{
   int retVal;
   unsigned short int DigOut, DigVal;
   char  BufKey[16];

   printf("Enter OUTPUTs to set(0x00 .. 0x03FF):");
   getEntry(BufKey);
	DigOut = (unsigned short int) strtol((const char *)&BufKey, NULL, 16);
	printf("Enter OUPUT values:");
   getEntry(BufKey);
	DigVal = (unsigned short int) strtol((const char *)&BufKey, NULL, 16);
   retVal = (*FncDIGIO_Set_All_DOUT)( DigOut, DigVal);
   if( retVal == NO_ERROR ) {
      printf(" OUTPUTS 0x%hx = 0x%hx", DigOut, DigVal);
   } else {
      printf("Error %d setting Outputs 0x%hx to 0x%hx\r\n", retVal, DigOut, DigVal);
   }
   return retVal;
}

static int Config_Interrupts( void)
{
   int ReturnCode;
   unsigned char InNumber;
   unsigned char EdgeValue;
   unsigned short int NumInts;
   char  BufKey[16];

   printf("Enter input number (0...9) or power fail input (14):");
   getEntry(BufKey);
   InNumber = (unsigned char) atoi(BufKey);
   printf("Enter edge (0:falling, 1:rising, 2:both):");
   getEntry(BufKey);
   EdgeValue = (unsigned char) atoi(BufKey);
   printf("Enter number of interrupts:");
   getEntry(BufKey);
   NumInts = (unsigned short int) atoi(BufKey);
   ReturnCode = ( *FncDIGIO_ConfigureInterruptService)( InNumber, EdgeValue, (void (*)(input_int_t))&InputIntHandler, NumInts);
   if( ReturnCode) {
      printf("ERROR %d in config interrupt\n", ReturnCode);
   } else {
      printf("Interrupt on input %hhu configured\n", InNumber);
   }
   return ReturnCode;
}

static void InputIntHandler( input_int_t wInState)
{
   printf("InputIntHandler: Input %hhu interrupt, value %hhu\r\n", wInState.InputNumber, wInState.InputValue);
}

static int Get_Interrupts( void)
{
   int ReturnCode;
   unsigned char InNumber;
   unsigned long TotalInts;
   char  BufKey[16];

   printf("Enter input number (0...9):");
   getEntry(BufKey);
   InNumber = (unsigned char) atoi(BufKey);
   ReturnCode = ( *FncDIGIO_GetNumberOfInterrupts)( InNumber, &TotalInts);
   if( ReturnCode) {
      printf("ERROR %d in getting number of interrupts\n", ReturnCode);
   } else {
      printf("Number of interrupts %lu for input %hhu\n", TotalInts, InNumber);
   }
   return ReturnCode;
}

static int Remove_Interrupts( void)
{
   int ReturnCode;
   unsigned char InNumber;
   char  BufKey[16];

   printf("Enter input number (0...9):");
   getEntry(BufKey);
   InNumber = (unsigned char) atoi(BufKey);
   ReturnCode = ( *FncDIGIO_RemoveInterruptService)( InNumber);
   if( ReturnCode) {
      printf("ERROR %d in remove interrupt\n", ReturnCode);
   } else {
      printf("Interrupt for Input %hhu removed\n", InNumber);
   }
   return ReturnCode;
}

static int Test_Timers( void)
{
   int ReturnCode;
   char  BufKey[16];
   unsigned char Action;
   unsigned char TimerNumber = 0xff;;

   printf("Enter action (0:get, 1:start, 2:stop, 3:free, 4: re-start:");
   getEntry(BufKey);
   Action = (unsigned char) atoi(BufKey);
   switch( Action) {
      case 0:
         ReturnCode = (*FncOWASYS_GetTimer)( &TimerNumber, (void (*)(unsigned char))TimerHandler, 10, 0);
         if( ReturnCode) {
            printf("ERROR %d Getting a timer\n", ReturnCode);
         } else {
            printf("TIMER %hhu assigned OK\n", TimerNumber);
         }
         break;
      case 1:
         printf("Enter timer number:");
         getEntry(BufKey);
         TimerNumber = (unsigned char) atoi(BufKey);
         ReturnCode = (*FncOWASYS_StartTimer)( TimerNumber, ONE_TICK);
         if( ReturnCode) {
            printf("ERROR %d starting timer %hhu\n", ReturnCode, TimerNumber);
         } else {
            printf("TIMER %hhu started OK\n", TimerNumber);
         }
         break;
      case 2:
         printf("Enter timer number:");
         getEntry(BufKey);
         TimerNumber = (unsigned char) atoi(BufKey);
         ReturnCode = (*FncOWASYS_StopTimer)( TimerNumber);
         if( ReturnCode) {
            printf("ERROR %d stopping timer %hhu\n", ReturnCode, TimerNumber);
         } else {
            printf("TIMER %hhu stopped OK\n", TimerNumber);
         }
         break;
      case 3:
         printf("Enter timer number:");
         getEntry(BufKey);
         TimerNumber = (unsigned char) atoi(BufKey);
         ReturnCode = (*FncOWASYS_FreeTimer)( TimerNumber);
         if( ReturnCode) {
            printf("ERROR %d freeing timer %hhu\n", ReturnCode, TimerNumber);
         } else {
            printf("TIMER %hhu freed OK\n", TimerNumber);
         }
         break;
      case 4:
         printf("Enter timer number:");
         getEntry(BufKey);
         TimerNumber = (unsigned char) atoi(BufKey);
         ReturnCode = (*FncOWASYS_RestartTimer)( TimerNumber);
         if( ReturnCode) {
            printf("ERROR %d re-starting timer %hhu\n", ReturnCode, TimerNumber);
         } else {
            printf("TIMER %hhu re-started OK\n", TimerNumber);
         }
         break;
      default:
         printf("Unknown action\n");
         return -1;
   }
   return ReturnCode;
}

static void TimerHandler( unsigned char nTimer)
{
   printf("TimerHandler: Timer %hhu expired\r\n", nTimer);
}

static int Rx_RS485( unsigned char wResp)
{
   int ReturnCode = NO_ERROR;
   int y, x, i;
   char RxBuf[12];

   if( FD_485 == -1) {
      ReturnCode = OpenUart485();
      if(ReturnCode) {
         printf("Error %d opening RS485\n", ReturnCode);
         return -1;
      }
   }

   y = 0;
   memset (RxBuf, 0, 12);
   while( y < 200) {
      i = read(FD_485, RxBuf, 12);
      if( i > 0) {
         printf("RECEIVED %d charACTERS\r\n", i);
         y = 0;
         for( x=0; x<i; x++) {
            printf("RECEIVED(0x%x)\r\n", RxBuf[x]);
         }
         if( RxBuf[0] == 0xcc) {
            break;
         }
      } else {
         (*Fncusecsleep)(0, 10000);
         y++;
      }
   }
   if(y < 200) {
      if( wResp) {
         //TO-DO Send message
      }
   } else {
      printf("Error receiving Rs485\r\n");
   }
   return ReturnCode;
}

static int Tx_RS485( void)
{
   int ReturnCode = NO_ERROR;
   unsigned char  DestAddr, MyAddr;
   char  BufKey[6];
   ssize_t written;
//   unsigned int aLSR=0;

   if( FD_485 == -1) {
      ReturnCode = OpenUart485();
      if(ReturnCode) {
         printf("Error %d opening RS485\n", ReturnCode);
         return -1;
      }
   }
#if 0
   /* Enable RS485 mode: */
	rs485conf.flags |= SER_RS485_ENABLED;
   /* Set logical level for RTS pin equal to 1 when sending: */
	rs485conf.flags &= ~(SER_RS485_RTS_ON_SEND);
//	rs485conf.flags |= SER_RS485_RTS_ON_SEND;
   /* Set logical level for RTS pin equal to 0 after sending: */
	rs485conf.flags |= SER_RS485_RTS_AFTER_SEND;
//   rs485conf.flags &= ~(SER_RS485_RTS_AFTER_SEND);
   /* Set rts delay ms before send, if needed: */
	rs485conf.delay_rts_before_send = 1;
	/* Set rts delay ms after send, if needed: */
	rs485conf.delay_rts_after_send = 1;

   if ( (retVal = ioctl (FD_485, TIOCSRS485, &rs485conf)) < 0) {
		printf("Error setting RS485, retVal(%d), errno(%d)(%s)\n", retVal, errno, strerror(errno));
      return -1;
	}
#endif
   printf("Enter Destination Address (0...255):");
   getEntry(BufKey);
   DestAddr = atoi(BufKey);
   printf("Enter Local Address (0...255):");
   getEntry(BufKey);
   MyAddr = atoi(BufKey);
   CheckMsg[1] = DestAddr;
   CheckMsg[3] = MyAddr;
   written = write(FD_485, &CheckMsg[0], strlen(CheckMsg));
   if( written != (int)strlen(CheckMsg)) {
      printf("ERROR SENDING MESSAGE\r\n");
   } else {
      printf("SENT MESSAGE\r\n");
   }

//   while(1) {
//      ioctl(FD_485, TIOCSERGETLSR, &aLSR);
//      if(aLSR & TIOCSER_TEMT)
//         break;
//   }

   Rx_RS485( 0);
   return ReturnCode;
}

static int OpenUart485( void)
{
   int ReturnCode;

   FD_485 = open( UART_RS485, O_RDWR | O_NOCTTY | O_NONBLOCK );
   if( FD_485 < 0) {
      printf("open %s error %s\n", UART_RS485, strerror(errno));
      return -1;
   }

   ReturnCode = tcgetattr(FD_485, &oldtio);
   if( ReturnCode < 0 ) {
      printf("tcgetattr error %s\n", strerror(errno));
      close(FD_485);
      FD_485 = -1;
      return -1;
   }

   newtio = oldtio;
   newtio.c_cflag |= B115200 | CS8 | CLOCAL | CREAD;
   newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;    // no output modes
	newtio.c_lflag = 0;    // no canonical, no echo, ...
   newtio.c_cc[VMIN] = 0;
  	newtio.c_cc[VTIME] = 0;

	ReturnCode = cfsetospeed(&newtio, B115200);
	if (ReturnCode < 0) {
      printf("Could not set output speed!\n");
      close(FD_485);
      FD_485 = -1;
		return -1;
	}
	ReturnCode = cfsetispeed(&newtio, B115200);
	if (ReturnCode < 0) {
      printf("Could not set input speed!\n");
      close(FD_485);
      FD_485 = -1;
		return -1;
	}
   tcflush  ( FD_485, TCIOFLUSH);
   tcsetattr( FD_485, TCSANOW, &newtio);
   printf(" %s configured succesfully.\n", UART_RS485);
   return 0;
}

static int Set_Adc_Range( void)
{
   int value, retVal;
   unsigned char  readvalue;
   char  BufKey[16];

   printf("Enter ADC_RANGE number (0..3):");
   getEntry(BufKey);
   value = atoi(BufKey);
   printf("Enter ADC_RANGE value (0..1):");
   getEntry(BufKey);
   readvalue = atoi(BufKey);
   retVal = (*FncDIGIO_Set_ADC_RANGE)((unsigned char)value, readvalue);
   if( retVal == NO_ERROR ) {
      printf(" ADC%d_RANGE = %hhu", value, readvalue);
   } else {
      printf("Error %d setting ADC%d_RANGE\r\n", retVal, value);
   }
   return retVal;
}

static int Enable_RS485( void)
{
   int ReturnCode;
   unsigned char wValue;
   char  BufKey[16];

   printf("Disable(0), Enable(1):");
   getEntry(BufKey);
   wValue = (unsigned char) atoi(BufKey);
   ReturnCode = (*FncDIGIO_Enable_RS485)(wValue);
   if( ReturnCode == NO_ERROR ) {
      printf(" ENABLE RS485 OK\r\n");
   } else {
      printf("Error %d enabling RS485\r\n", ReturnCode);
   }
   return ReturnCode;
}

static int Enable_KLine( void)
{
   int ReturnCode;
   unsigned char wValue;
   char  BufKey[16];

   printf("Disable(0), Enable(1):");
   getEntry(BufKey);
   wValue = (unsigned char) atoi(BufKey);
   ReturnCode = (*FncDIGIO_Enable_KLINE)(wValue);
   if( ReturnCode == NO_ERROR ) {
      printf(" K-LINE %s OK\r\n", wValue ? "enabled" : "disabled" );
   } else {
      printf("Error %d enabling K-LINE\r\n", ReturnCode);
   }
   return ReturnCode;
}

static int GetVin( void)
{
  int ReturnCode = 0;
  float ad_vin;

  ReturnCode = (*FncRTUGetAD_V_IN) ( &ad_vin);
  if( ReturnCode) {
    printf("ERROR %d getting Vin analog input\n", ReturnCode);
  } else {
    printf("Vin level: %f\n", ad_vin);
  }
  return ReturnCode;
}

static int GetVbat( void)
{
  int ReturnCode = 0;
  float ad_vbat;

  ReturnCode = (*FncRTUGetAD_VBAT_MAIN) ( &ad_vbat);
  if( ReturnCode) {
    printf("ERROR %d getting Vbat analog input\n", ReturnCode);
  } else {
    printf("%f", ad_vbat);
    fflush(stdout);
  }
  return ReturnCode;
}

static int GetTemp( void)
{
  int ReturnCode = 0;
  int temp;

  ReturnCode = (*FncRTUGetAD_TEMP) ( &temp);
  if( ReturnCode) {
    printf("ERROR %d getting temperature\n", ReturnCode);
  } else {
    printf("Temperature: %d C\n", temp);
  }
  return ReturnCode;
}

void iButtonInterruptHandler(unsigned char *pData)
{
   int i;

   // This should not be done in a real app because it is a handler
   // but it is only for showing and testing the funcitonality
   printf("iButton (interrupt) detected with ID: ");

   for(i = 0; i < IB_ID_LENGTH; i ++)
   {
      printf("0x%hhX ", pData[i]);
   }
   printf("\n");
}

static int Set_VOUT( void)
{
   int ReturnCode;
   unsigned char  value;
   char  BufKey[6];

   printf("Enter 1/Enable, 0/Disable:");
   getEntry(BufKey);
   value = atoi(BufKey);

   ReturnCode = (*FncDIGIO_Set_VOUT)(value);
   if( ReturnCode == NO_ERROR ) {
      printf(" VOUT %s OK\r\n", value ? "Enabled" : "Disabled");
   } else {
      printf("Error %d setting VOUT\r\n", ReturnCode);
   }
   return ReturnCode;
}

static int Get_VOUT_STATUS( void)
{
   int retVal;
   unsigned char  readvalue;

   retVal = (*FncDIGIO_Get_VOUT_STATUS)( &readvalue);
   if( retVal == NO_ERROR ) {
      printf(" VOUT_STATUS(%hhu)(%s)\r\n", readvalue, readvalue ? "OK" : "ERROR");
   } else {
      printf("Error %d getting VOUT_STATUS\r\n", retVal);
   }
   return retVal;
}

static int Get_PWR_FAIL( void)
{
   int retVal;
   unsigned char  readvalue;

   retVal = (*FncDIGIO_Get_PWR_FAIL)( &readvalue);
   if( retVal == NO_ERROR ) {
      printf(" PWR_FAIL(%hhu)(%s)\r\n", readvalue, readvalue ? "ERROR" : "OK");
   } else {
      printf("Error %d getting PWR_FAIL\r\n", retVal);
   }
   return retVal;
}

static int EnableCan( void)
{
   int ReturnCode = 0;
   char wValue;
   char  BufKey[16];

   printf("Disable(0), Enable(1):");
   getEntry(BufKey);
   wValue = (unsigned char) atoi(BufKey);
   if( (ReturnCode = (*FncDIGIO_Enable_Can)( wValue)) != NO_ERROR )
   {
      printf("ERROR(%d) %s CAN\n", ReturnCode, wValue ? "ENABLE" : "DISABLE");
   }
   else
   {
      printf("CAN %s OK\n", wValue ? "ENABLE" : "DISABLE");
   }
   return ReturnCode;
}

static int Set_SD_Card( void)
{
   int ReturnCode;
   unsigned char  value;
   char  BufKey[6];

   printf("Enter 1/Enable, 0/Disable:");
   getEntry(BufKey);
   value = atoi(BufKey);

   ReturnCode = (*FncDIGIO_Set_SD_Card)(value);
   if( ReturnCode == NO_ERROR ) {
      printf(" SD %s OK\r\n", value ? "Enabled" : "Disabled");
   } else {
      printf("Error %d setting SD Card\r\n", ReturnCode);
   }
   return ReturnCode;
}

static int Get_USB_A( void)
{
   int retVal;
   unsigned char  readvalue;

   retVal = (*FncDIGIO_Get_USB_A)( &readvalue);
   if( retVal == NO_ERROR ) {
      printf(" USB_A(%hhu)(%s)\r\n", readvalue, readvalue ? "OK" : "ERROR");
   } else {
      printf("Error %d getting USB_A\r\n", retVal);
   }
   return retVal;
}

static int DiscoverOneWire( void)
{
   int ReturnCode;
   OneWireTable_t *pDeviceList = NULL;
   unsigned char ListSize, i;

   ReturnCode = (*FncOW_Discover)( &pDeviceList, &ListSize);
   if (ReturnCode == NO_ERROR){
      printf("1-Wire discover OK\n");
      printf("Devices(%hhu)\n", ListSize);
      for( i=0; i<ListSize; i++){
         printf("Device (%hhu): (%s) %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX\n", i, StatusDevice[pDeviceList->DeviceStatus],
                 pDeviceList[i].DeviceId.RomId[0], pDeviceList[i].DeviceId.RomId[1], pDeviceList[i].DeviceId.RomId[2],
                 pDeviceList[i].DeviceId.RomId[3], pDeviceList[i].DeviceId.RomId[4], pDeviceList[i].DeviceId.RomId[5],
                 pDeviceList[i].DeviceId.RomId[6], pDeviceList[i].DeviceId.RomId[7]);
      }
      if( pDeviceList != NULL){
         // free pointer
         free(pDeviceList);
      }
   } else{
      printf("1-Wire discover ERROR(%d)\n", ReturnCode);
   }
   return ReturnCode;
}

static int UpdateOneWire( void){
   int ReturnCode;
   unsigned char UpdateTime;
   char Bufkey[1];

   printf("Enter 1-Wire device list update time(1 - 50):");
   getEntry(Bufkey);
   UpdateTime = (unsigned char) atoi(Bufkey);
   if((ReturnCode = (*FncOW_SetUpdate)(OwUpdateInterruptHandler, UpdateTime)) != NO_ERROR){
      printf("1-Wire interrupt handler ERROR (%d)\n", ReturnCode);
   } else{
      printf("1-Wire interrupt handler set OK\n");
   }
   return ReturnCode;
}

//This is an example. Code inside must be as short and fast as possible, for example only to post a semaphore
//and execute the interruption code in a different thread out of the handler
void OwUpdateInterruptHandler(OneWireTable_t * pDevices, unsigned char wNumber, int wError)
{
	OneWireTable_t *pLocalDevice = pDevices;
	unsigned char i;

	printf("OwUpdateInterruptHandler ENTER\r\n");
	if( wError != NO_ERROR) {
		printf("ERROR(%d)\n", wError);
	} else {
		printf("NUM DEVICES(%hhu)\n", wNumber);
		for( i=0; i<wNumber; i++) {
			printf("Device (%hhu):(%s) %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX\n", i, StatusDevice[pLocalDevice->DeviceStatus],
				pLocalDevice->DeviceId.RomId[0], pLocalDevice->DeviceId.RomId[1], pLocalDevice->DeviceId.RomId[2],
				pLocalDevice->DeviceId.RomId[3], pLocalDevice->DeviceId.RomId[4], pLocalDevice->DeviceId.RomId[5],
				pLocalDevice->DeviceId.RomId[6], pLocalDevice->DeviceId.RomId[7] );
			pLocalDevice++;
		}
		printf("\n");
	}
}

static int ResetUpdateOneWire ( void)
{
   int ReturnCode;

   if( (ReturnCode = (*FncOW_ResetUpdate)()) != NO_ERROR){
      printf("1-Wire interrupt handler reset ERROR (%d)\n", ReturnCode);
   } else{
      printf("1-Wire interrupt handler reset OK\n");
   }
   return ReturnCode;
}

static int Set_CAN_TX_Mode( char number)
{
   int ReturnCode = 0;
   unsigned char wValue;
   char  BufKey[16];

   printf("Fast(0), Disable(1), Slow(2):");
   getEntry(BufKey);
   wValue = (unsigned char) atoi(BufKey);

   switch( number) {
      case 1:
         ReturnCode = (*FncDIGIO_Set_CAN1_TX_Mode)( wValue);
         break;
      case 2:
         ReturnCode = (*FncDIGIO_Set_CAN2_TX_Mode)( wValue);
         break;
      case 3:
         ReturnCode = (*FncDIGIO_Set_CAN3_TX_Mode)( wValue);
         break;
      case 4:
         ReturnCode = (*FncDIGIO_Set_CAN4_TX_Mode)( wValue);
         break;
      default:
         ReturnCode = -1;
         break;
   }

   if( ReturnCode != NO_ERROR )
   {
      printf("ERROR(%d) SET CAN%dTX MODE\n", ReturnCode, number);
   }
   else
   {
      printf("SET CAN%dTX MODE %d OK\n", number, wValue);
   }
   return ReturnCode;
}

static int Switch_GPS( void)
{
   int ReturnCode = 0;
   unsigned char wValue;
   char  BufKey[16];

   printf("OFF(0), ON(1):");
   getEntry(BufKey);
   wValue = (unsigned char) atoi(BufKey);
   if( (ReturnCode = (*FncDIGIO_Switch_GPS_ON_OFF)( wValue)) != NO_ERROR )
   {
      printf("ERROR(%d) %s GPS\n", ReturnCode, wValue ? "ENABLE" : "DISABLE");
   }
   else
   {
      printf("GPS %s OK\n", wValue ? "ENABLE" : "DISABLE");
   }
   return ReturnCode;
}

static int Set_KLINE1_Threshold( void)
{
   int ReturnCode = 0;
   char wValue;
   char  BufKey[16];

   printf("LOW(0), HIGH(1):");
   getEntry(BufKey);
   wValue = (unsigned char) atoi(BufKey);
   if( (ReturnCode = (*FncDIGIO_Set_KLINE1_Threshold)( wValue)) != NO_ERROR )
   {
      printf("ERROR(%d) SETTING %s KLINE1 THRESHOLD\n", ReturnCode, wValue ? "HIGH" : "LOW");
   }
   else
   {
      printf("KLINE1 THRESHOLD %s OK\n", wValue ? "HIGH" : "LOW");
   }
   return ReturnCode;
}

static int Set_KLINE2_Threshold( void)
{
   int ReturnCode = 0;
   char wValue;
   char  BufKey[16];

   printf("LOW(0), HIGH(1):");
   getEntry(BufKey);
   wValue = (unsigned char) atoi(BufKey);
   if( (ReturnCode = (*FncDIGIO_Set_KLINE2_Threshold)( wValue)) != NO_ERROR )
   {
      printf("ERROR(%d) SETTING %s KLINE2 THRESHOLD\n", ReturnCode, wValue ? "HIGH" : "LOW");
   }
   else
   {
      printf("KLINE2 THRESHOLD %s OK\n", wValue ? "HIGH" : "LOW");
   }
   return ReturnCode;
}

static int Get_Bat_Stat( void)
{
    int ReturnCode = 0;
    unsigned char BattState=0;
   
    if( (ReturnCode = (*FncRTUGetBatteryState)(&BattState)) != NO_ERROR )
    {
        printf("ERROR %d getting battery state\n", ReturnCode);
    }
    else
    {
        printf("Battery state(%d)\n", BattState);
        switch(BattState) {
            case 0:
                printf("Precharge in progress\n");
                break; 
            case 1:
                printf("Charge done\n");
                break; 
            case 2:
                printf("Fast charge\n");
                break; 
            case 3:
                printf("Charge suspended\n");
                break;
            }
    }

    return ReturnCode;
}

static int Get_Bat_Charge_Stat( void)
{
    int ReturnCode = 0;
    unsigned char BattStatus;

    ReturnCode = (*FncRTUGetBatteryChargeStatus)( &BattStatus);
    if( ReturnCode != NO_ERROR ) {
        printf("Reading Battery charge status error (%d)...\n", ReturnCode);
    } else {
	    printf("Battery charge status is %s\n", BattStatus ? "ENABLED" : "DISABLED");
    } 

   return ReturnCode;
}

static int Set_Bat_Charge_Stat( void)
{
    int ReturnCode = 0;
    unsigned char wEnable;
    char  BufKey[16];

    printf("Disable charging(0), Enable charging(1):");
    getEntry(BufKey);
    wEnable= (unsigned char) atoi(BufKey);
            
    ReturnCode = (*FncRTUSetBatteryChargeStatus)( wEnable);
    if( ReturnCode != NO_ERROR ) {
        printf("Error (%d) %s Charge status...\n", ReturnCode, wEnable ? "ENABLING" : "DISABLING");
    } else {
        printf("Charge status %s OK...\n", wEnable ? "ENABLED" : "DISABLED");
    }

   return ReturnCode;
}
