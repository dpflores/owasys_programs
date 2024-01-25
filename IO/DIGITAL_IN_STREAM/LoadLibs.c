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
//** Description:
//**
//** Filename:      LoadLibs.cpp
//** Owner:         Owasys
//** Creation date: 15/12/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** V1.0.0   15/12/2017 Created                            owasys
//*********************************************************************

#define __LOAD_LIBS_CPP

//-----------------------------------------------------------------//
// System Includes
//-----------------------------------------------------------------//
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

//-----------------------------------------------------------------//
// User Includes
//-----------------------------------------------------------------//
#include "LoadLibs.h"
#include "owa4x_AN3.h"

//-----------------------------------------------------------------//
// Defines
//-----------------------------------------------------------------//

//-----------------------------------------------------------------//
// Macros
//-----------------------------------------------------------------//

//-----------------------------------------------------------------//
// External variables
//-----------------------------------------------------------------//

//-----------------------------------------------------------------//
// External functions
//-----------------------------------------------------------------//

//-----------------------------------------------------------------//
// Private variables
//-----------------------------------------------------------------//

/* Functions definition */

//-----------------------------------------------------------------//
// Function: LoadExternalLibrary()
// Input Params:
//                *wLibraryName: library name string
//                **wLibHandle: pointer to the handler of the
//                              dynamic library
// Output Params:
// Description:
//    Loads a dynamic library from the file named wLibraryName.
//-----------------------------------------------------------------//
void LoadExternalLibrary(char *wLibraryName, void **wLibHandle)
{
   *wLibHandle = dlopen(wLibraryName, RTLD_LAZY);
   if (!*wLibHandle)
   {
      WriteLog("No shared library %s found", wLibraryName);
      printf("%s\n", dlerror());
      exit(1);
   }
}

//-----------------------------------------------------------------//
// Function: UnloadExternalLibrary()
// Input Params:
//                *wLibHandle: pointer to the handler of the
//                             dynamic library
// Output Params:
// Description:
//    Unloads a dynamic library.
//-----------------------------------------------------------------//
int UnloadExternalLibrary(void *wLibHandle)
{
   if ((dlclose(wLibHandle)) != 0)
   {
      WriteLog("UnloadExternalLibrary() error");
      exit(1);
   }
   // WriteLog("UnloadExternalLibrary() ok");
   return 0;
}

//-----------------------------------------------------------------//
// Function: LoadIOSFunctions()
// Input Params:
//                *wLibHandle: pointer to the handler of the
//                             dynamic library
// Output Params:
// Description:
//    Calls to dlsym to get the addresses where the functions of
//    the library are loaded to be used in the program.
//-----------------------------------------------------------------//
void LoadIOSFunctions(void *wLibHandle)
{
   FncIO_Initialize = (int (*)(void))dlsym(wLibHandle, "IO_Initialize");
   if (dlerror() != NULL)
   {
      WriteLog("No IO_Initialize() found");
   }
   FncIO_Start = (int (*)(void))dlsym(wLibHandle, "IO_Start");
   if (dlerror() != NULL)
   {
      WriteLog("No IO_Start() found");
   }
   FncIO_Finalize = (int (*)(void))dlsym(wLibHandle, "IO_Finalize");
   if (dlerror() != NULL)
   {
      WriteLog("No IO_Finalize() found");
   }
   FncIO_IsActive = (int (*)(int *))dlsym(wLibHandle, "IO_IsActive");
   if (dlerror() != NULL)
   {
      WriteLog("No IO_IsActive() found");
   }
   FncDIGIO_Set_ADC_RANGE = (int (*)(unsigned char, unsigned char))dlsym(wLibHandle, "DIGIO_Set_ADC_RANGE");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_ADC_RANGE() found");
   }
   FncDIGIO_Set_LED_SW0 = (int (*)(unsigned char))dlsym(wLibHandle, "DIGIO_Set_LED_SW0");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_LED_SW0() found");
   }

   FncDIGIO_Set_LED_SW0_Input = (int (*)(void))dlsym(wLibHandle, "DIGIO_Set_LED_SW0_Input");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_LED_SW0_Input() found");
   }

   FncDIGIO_Set_LED_SW1 = (int (*)(unsigned char))dlsym(wLibHandle, "DIGIO_Set_LED_SW1");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_LED_SW1() found");
   }
   FncDIGIO_Set_LED_SW2 = (int (*)(unsigned char))dlsym(wLibHandle, "DIGIO_Set_LED_SW2");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_LED_SW2() found");
   }
   FncDIGIO_Set_PPS_GPS = (int (*)(unsigned char))dlsym(wLibHandle, "DIGIO_Set_PPS_GPS");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_PPS_GPS() found");
   }
   FncANAGIO_GetAnalogIn = (int (*)(int, int *))dlsym(wLibHandle, "ANAGIO_GetAnalogIn");
   if (dlerror() != NULL)
   {
      WriteLog("No ANAGIO_GetAnalogIn() found");
   }
   // Interrupt
   FncDIGIO_ConfigureInterruptService = (int (*)(unsigned char, unsigned char, void (*)(input_int_t), unsigned short int))dlsym(wLibHandle, "DIGIO_ConfigureInterruptService");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_ConfigureInterruptService() found");
   }
   FncDIGIO_GetNumberOfInterrupts = (int (*)(unsigned char, unsigned long *))dlsym(wLibHandle, "DIGIO_GetNumberOfInterrupts");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_GetNumberOfInterrupts() found");
   }
   FncDIGIO_RemoveInterruptService = (int (*)(unsigned char))dlsym(wLibHandle, "DIGIO_RemoveInterruptService");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_RemoveInterruptService() found");
   }
   FncDIGIO_Get_DIN = (int (*)(unsigned char, unsigned char *))dlsym(wLibHandle, "DIGIO_Get_DIN");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Get_DIN found");
   }
   FncDIGIO_Get_All_DIN = (int (*)(unsigned short int *))dlsym(wLibHandle, "DIGIO_Get_All_DIN");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Get_All_DIN found");
   }
   FncDIGIO_Set_DOUT = (int (*)(unsigned char, unsigned char))dlsym(wLibHandle, "DIGIO_Set_DOUT");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_DOUT found");
   }
   FncDIGIO_Set_All_DOUT = (int (*)(unsigned short int, unsigned short int))dlsym(wLibHandle, "DIGIO_Set_All_DOUT");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_All_DOUT found");
   }
   FncDIGIO_Enable_RS485 = (int (*)(char))dlsym(wLibHandle, "DIGIO_Enable_RS485");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Enable_RS485 found");
   }
   FncDIGIO_Enable_KLINE = (int (*)(char))dlsym(wLibHandle, "DIGIO_Enable_KLINE");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Enable_KLINE found");
   }
   FncDIGIO_Get_USB_A = (int (*)(unsigned char *))dlsym(wLibHandle, "DIGIO_Get_USB_A");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Get_USB_A found");
   }
   FncDIGIO_Enable_Uart5 = (int (*)(unsigned char))dlsym(wLibHandle, "DIGIO_Enable_Uart5");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Enable_Uart5 found");
   }
   FncDIGIO_Set_SD_Card = (int (*)(unsigned char))dlsym(wLibHandle, "DIGIO_Set_SD_Card");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_SD_Card found");
   }
   // iButton
   FncIBUTTON_Reset = (int (*)(void))dlsym(wLibHandle, "IBUTTON_Reset");
   if (dlerror() != NULL)
   {
      WriteLog("No IBUTTON_Reset() found...\n");
   }
   FncIBUTTON_ReadByte = (int (*)(unsigned char *))dlsym(wLibHandle, "IBUTTON_ReadByte");
   if (dlerror() != NULL)
   {
      WriteLog("No IBUTTON_ReadByte() found...\n");
   }
   FncIBUTTON_WriteByte = (int (*)(unsigned char))dlsym(wLibHandle, "IBUTTON_WriteByte");
   if (dlerror() != NULL)
   {
      WriteLog("No IBUTTON_WriteByte() found...\n");
   }
   FncIBUTTON_ReadID = (int (*)(unsigned char *))dlsym(wLibHandle, "IBUTTON_ReadID");
   if (dlerror() != NULL)
   {
      WriteLog("No IBUTTON_ReadID() found...\n");
   }
   FncIBUTTON_CfgInt = (int (*)(void (*)(unsigned char *)))dlsym(wLibHandle, "IBUTTON_CfgInt");
   if (dlerror() != NULL)
   {
      WriteLog("No IBUTTON_CfgInt() found...\n");
   }
   FncIBUTTON_RemoveInt = (int (*)(void))dlsym(wLibHandle, "IBUTTON_RemoveInt");
   if (dlerror() != NULL)
   {
      WriteLog("No IBUTTON_RemoveInt() found...\n");
   }
   FncDIGIO_Set_VOUT = (int (*)(unsigned char))dlsym(wLibHandle, "DIGIO_Set_VOUT");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Set_VOUT found");
   }
   FncDIGIO_Enable_Can = (int (*)(char))dlsym(wLibHandle, "DIGIO_Enable_Can");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Enable_Can found");
   }
   FncDIGIO_Get_VOUT_STATUS = (int (*)(unsigned char *))dlsym(wLibHandle, "DIGIO_Get_VOUT_STATUS");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Get_VOUT_STATUS found");
   }
   FncDIGIO_Get_PWR_FAIL = (int (*)(unsigned char *))dlsym(wLibHandle, "DIGIO_Get_PWR_FAIL");
   if (dlerror() != NULL)
   {
      WriteLog("No DIGIO_Get_PWR_FAIL found");
   }
   FncOW_Discover = (int (*)(OneWireTable_t **, unsigned char *))dlsym(wLibHandle, "OW_Discover");
   if (dlerror() != NULL)
   {
      WriteLog("No OW_Discover found");
   }
   FncOW_SetUpdate = (int (*)(void (*)(OneWireTable_t *, unsigned char, int), unsigned char))dlsym(wLibHandle, "OW_SetUpdate");
   if (dlerror() != NULL)
   {
      WriteLog("No OW_SetUpdate found");
   }
   FncOW_ResetUpdate = (int (*)(void))dlsym(wLibHandle, "OW_ResetUpdate");
   if (dlerror() != NULL)
   {
      WriteLog("No OW_ResetUpdate found");
   }
   FncDIGIO_Set_CAN1_TX_Mode = (int (*)(char))dlsym(wLibHandle, "DIGIO_Set_CAN1_TX_Mode");
   if (dlerror() != NULL)
   {
      printf("No DIGIO_Set_CAN1_TX_Mode found\r\n");
   }
   FncDIGIO_Set_CAN2_TX_Mode = (int (*)(char))dlsym(wLibHandle, "DIGIO_Set_CAN2_TX_Mode");
   if (dlerror() != NULL)
   {
      printf("No DIGIO_Set_CAN2_TX_Mode found\r\n");
   }
   FncDIGIO_Set_CAN3_TX_Mode = (int (*)(char))dlsym(wLibHandle, "DIGIO_Set_CAN3_TX_Mode");
   if (dlerror() != NULL)
   {
      printf("No DIGIO_Set_CAN3_TX_Mode found\r\n");
   }
   FncDIGIO_Set_CAN4_TX_Mode = (int (*)(char))dlsym(wLibHandle, "DIGIO_Set_CAN4_TX_Mode");
   if (dlerror() != NULL)
   {
      printf("No DIGIO_Set_CAN4_TX_Mode found\r\n");
   }
   FncDIGIO_Switch_GPS_ON_OFF = (int (*)(unsigned char))dlsym(wLibHandle, "DIGIO_Switch_GPS_ON_OFF");
   if (dlerror() != NULL)
   {
      printf("No DIGIO_Switch_GPS_ON_OFF found\r\n");
   }
   FncDIGIO_Set_KLINE1_Threshold = (int (*)(char))dlsym(wLibHandle, "DIGIO_Set_KLINE1_Threshold");
   if (dlerror() != NULL)
   {
      printf("No DIGIO_Set_KLINE1_Threshold found\r\n");
   }
   FncDIGIO_Set_KLINE2_Threshold = (int (*)(char))dlsym(wLibHandle, "DIGIO_Set_KLINE2_Threshold");
   if (dlerror() != NULL)
   {
      printf("No DIGIO_Set_KLINE2_Threshold found\r\n");
   }
}

//-----------------------------------------------------------------//
// Function: LoadRTUControlFunctions()
// Input Params:
// Output Params:
// Description:
//-----------------------------------------------------------------//
void LoadRTUControlFunctions(void *wLibHandle)
{
   FncRTUControl_Initialize = (int (*)(void *))dlsym(wLibHandle, "RTUControl_Initialize");
   if (dlerror() != NULL)
   {
      WriteLog("No RTUControl_Initialize() found");
   }
   FncRTUControl_Start = (int (*)(void))dlsym(wLibHandle, "RTUControl_Start");
   if (dlerror() != NULL)
   {
      WriteLog("No RTUControl_Start() found");
   }
   FncRTUControl_Finalize = (int (*)(void))dlsym(wLibHandle, "RTUControl_Finalize");
   if (dlerror() != NULL)
   {
      WriteLog("No RTUControl_Finalize() found");
   }
   Fncusecsleep = (int (*)(int, int))dlsym(wLibHandle, "usecsleep");
   if (dlerror() != NULL)
   {
      WriteLog(" No usecsleep() found");
   }
   // Timers
   FncOWASYS_GetTimer = (int (*)(unsigned char *, void (*)(unsigned char), unsigned long, unsigned long))dlsym(wLibHandle, "OWASYS_GetTimer");
   if (dlerror() != NULL)
   {
      printf("No OWASYS_GetTimer() found...\n");
   }
   FncOWASYS_StartTimer = (int (*)(unsigned char, unsigned char))dlsym(wLibHandle, "OWASYS_StartTimer");
   if (dlerror() != NULL)
   {
      printf("No OWASYS_StartTimer() found...\n");
   }
   FncOWASYS_StopTimer = (int (*)(unsigned char))dlsym(wLibHandle, "OWASYS_StopTimer");
   if (dlerror() != NULL)
   {
      printf("No OWASYS_StopTimer() found...\n");
   }
   FncOWASYS_FreeTimer = (int (*)(unsigned char))dlsym(wLibHandle, "OWASYS_FreeTimer");
   if (dlerror() != NULL)
   {
      printf("No OWASYS_FreeTimer() found...\n");
   }
   FncOWASYS_RestartTimer = (int (*)(unsigned char))dlsym(wLibHandle, "OWASYS_RestartTimer");
   if (dlerror() != NULL)
   {
      printf("No OWASYS_RestartTimer() found...\n");
   }
   FncRTUGetAD_V_IN = (int (*)(float *))dlsym(wLibHandle, "RTUGetAD_V_IN");
   if (dlerror() != NULL)
   {
      printf("No RTUGetAD_V_IN() found...\n");
   }
   FncRTUGetAD_VBAT_MAIN = (int (*)(float *))dlsym(wLibHandle, "RTUGetAD_VBAT_MAIN");
   if (dlerror() != NULL)
   {
      printf("No RTUGetAD_VBAT_MAIN() found...\n");
   }
   FncRTUGetAD_TEMP = (int (*)(int *))dlsym(wLibHandle, "RTUGetAD_TEMP");
   if (dlerror() != NULL)
   {
      printf("No RTUGetAD_TEMP() found...\n");
   }
   FncRTUGetBatteryState = (int (*)(unsigned char *))dlsym(wLibHandle, "RTUGetBatteryState");
   if (dlerror() != NULL)
   {
      printf("No RTUGetBatteryState() found...\n");
   }
   FncRTUGetBatteryChargeStatus = (int (*)(unsigned char *))dlsym(wLibHandle, "RTUGetBatteryChargeStatus");
   if (dlerror() != NULL)
   {
      printf("No RTUGetBatteryChargeStatus() found...\n");
   }
   FncRTUSetBatteryChargeStatus = (int (*)(unsigned char))dlsym(wLibHandle, "RTUSetBatteryChargeStatus");
   if (dlerror() != NULL)
   {
      printf("No RTUSetBatteryChargeStatus() found...\n");
   }
}
