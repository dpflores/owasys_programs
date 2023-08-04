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
//** Project:      owa4x_AN3
//** Description:
//**
//** Filename:      LoadLibs.h
//** Owner:         Owasys
//** Creation date: 15/12/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** V1.0.0   15/12/2017 Created                            owasys
//*********************************************************************

#ifndef __LOAD_LIBS_H
   #define __LOAD_LIBS_H

//-----------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------//
#include <string.h>
#include <stdarg.h>
//#include <time.h>

//-----------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------//
#include "owa4x/owcomdefs.h"
#include "owa4x/pm_messages.h"
#include "owa4x/IOs_ModuleDefs.h"



//-----------------------------------------------------------------//
//Defines
//-----------------------------------------------------------------//

//-----------------------------------------------------------------//
//Macros
//-----------------------------------------------------------------//


   #ifdef __LOAD_LIBS_CPP
      void LoadExternalLibrary( char *wLibraryName, void **wLibHandle );
      int UnloadExternalLibrary( void *wLibHandle );
      void LoadIOSFunctions( void *wLibHandle );
      void LoadRTUControlFunctions( void *wLibHandle);
      int (*FncRTUControl_Initialize)( void *);
      int (*FncRTUControl_Start)( void);
      int (*FncRTUControl_Finalize)( void);
      int (*Fncusecsleep)(int,int);

      int (*FncIO_Initialize)( void );
      int (*FncIO_Start)( void);
      int (*FncIO_Finalize)( void);
      int (*FncIO_IsActive)( int *);
      int (*FncDIGIO_Set_ADC_RANGE)( unsigned char, unsigned char);
      int (*FncDIGIO_Set_LED_SW0)( unsigned char);
      int (*FncDIGIO_Set_LED_SW1)( unsigned char);
      int (*FncDIGIO_Set_LED_SW2)( unsigned char);
      int (*FncDIGIO_Set_PPS_GPS)( unsigned char);
      int (*FncANAGIO_GetAnalogIn)( int, int *);

      int ( *FncDIGIO_ConfigureInterruptService)( unsigned char wInput, unsigned char wEdge, void(*)(input_int_t), unsigned short int wNumInts );
      int ( *FncDIGIO_GetNumberOfInterrupts)( unsigned char wInput, unsigned long *pTotal );
      int ( *FncDIGIO_RemoveInterruptService)( unsigned char wInput );
      int (*FncDIGIO_Get_DIN)( unsigned char, unsigned char * );
      int (*FncDIGIO_Get_All_DIN)( unsigned short int * );
      int (*FncDIGIO_Set_DOUT)( unsigned char, unsigned char );
      int (*FncDIGIO_Set_All_DOUT)( unsigned short int, unsigned short int );
      //Timers
      int ( *FncOWASYS_GetTimer) ( unsigned char *, void (*)(unsigned char), unsigned long, unsigned long);
      int ( *FncOWASYS_StartTimer) ( unsigned char, unsigned char );
      int ( *FncOWASYS_StopTimer) ( unsigned char );
      int ( *FncOWASYS_FreeTimer) ( unsigned char );
      int ( *FncOWASYS_RestartTimer) ( unsigned char );

      int (*FncDIGIO_Enable_RS485)( char );
      int (*FncDIGIO_Enable_KLINE)( char );
      int (*FncDIGIO_Enable_Uart5)( unsigned char wValue );
      int (*FncDIGIO_Set_SD_Card)( unsigned char wValue );
      int (*FncDIGIO_Get_USB_A)( unsigned char *wValue );

      int (*FncRTUGetAD_V_IN)( float *);
      int (*FncRTUGetAD_VBAT_MAIN)( float *);
      int (*FncRTUGetAD_TEMP)( int *);
      int (*FncDIGIO_Set_CAN1_TX_Mode)( char );
      int (*FncDIGIO_Set_CAN2_TX_Mode)( char );
      int (*FncDIGIO_Set_CAN3_TX_Mode)( char );
      int (*FncDIGIO_Set_CAN4_TX_Mode)( char );
      int (*FncDIGIO_Switch_GPS_ON_OFF)( unsigned char);
      int (*FncDIGIO_Set_KLINE1_Threshold)( char );
      int (*FncDIGIO_Set_KLINE2_Threshold)( char );
      int (*FncRTUGetBatteryState)( unsigned char *wValue );
      int (*FncRTUGetBatteryChargeStatus)( unsigned char *wValue );
      int (*FncRTUSetBatteryChargeStatus)(  unsigned char wValue );
      
       //iButton
      int (*FncIBUTTON_Reset)(void);
      int (*FncIBUTTON_ReadByte)(unsigned char *);
      int (*FncIBUTTON_WriteByte)(unsigned char);
      int (*FncIBUTTON_ReadID)(unsigned char *);
      int (*FncIBUTTON_CfgInt)(void(*wHandler)(unsigned char *));
      int (*FncIBUTTON_RemoveInt)(void);
      
      int (*FncDIGIO_Set_VOUT)( unsigned char);
      int (*FncDIGIO_Get_VOUT_STATUS)( unsigned char *);
      int (*FncDIGIO_Get_PWR_FAIL)( unsigned char *);
      int (*FncDIGIO_Enable_Can)( char );
      
      //one wire
      int (*FncOW_Discover)( OneWireTable_t **, unsigned char *);
      int (*FncOW_SetUpdate)( void (*)(OneWireTable_t *, unsigned char, int), unsigned char);
      int (*FncOW_ResetUpdate)( void);


   #else
      extern void LoadExternalLibrary( char *wLibraryName, void **wLibHandle );
      extern int UnloadExternalLibrary( void *wLibHandle );
      extern void LoadIOSFunctions( void *wLibHandle );
      extern void LoadRTUControlFunctions( void *wLibHandle); 
      extern int (*FncRTUControl_Initialize)( void *);
      extern int (*FncRTUControl_Start)( void);
      extern int (*FncRTUControl_Finalize)( void);
      extern int (*Fncusecsleep)(int,int);

      extern int (*FncIO_Initialize)( void );
      extern int (*FncIO_Start)( void);
      extern int (*FncIO_Finalize)( void);
      extern int (*FncIO_IsActive)( int *);
      extern int (*FncDIGIO_Set_ADC_RANGE)( unsigned char, unsigned char);
      extern int (*FncDIGIO_Set_LED_SW0)( unsigned char);
      extern int (*FncDIGIO_Set_LED_SW1)( unsigned char);
      extern int (*FncDIGIO_Set_LED_SW2)( unsigned char);
      extern int (*FncDIGIO_Set_PPS_GPS)( unsigned char);
      extern int (*FncANAGIO_GetAnalogIn)( int, int *);

      extern int (*FncDIGIO_Set_LED_SW0_Input)( void);

      extern int ( *FncDIGIO_ConfigureInterruptService)( unsigned char wInput, unsigned char wEdge, void(*)(input_int_t), unsigned short int wNumInts);
      extern int ( *FncDIGIO_GetNumberOfInterrupts)( unsigned char wInput, unsigned long *pTotal );
      extern int ( *FncDIGIO_RemoveInterruptService)( unsigned char wInput );
      extern int (*FncDIGIO_Get_DIN)( unsigned char, unsigned char * );
      extern int (*FncDIGIO_Get_All_DIN)( unsigned short int * );
      extern int (*FncDIGIO_Set_DOUT)( unsigned char, unsigned char );
      extern int (*FncDIGIO_Set_All_DOUT)( unsigned short int, unsigned short int );
      //Timers
      extern int ( *FncOWASYS_GetTimer) ( unsigned char *, void (*)(unsigned char), unsigned long, unsigned long);
      extern int ( *FncOWASYS_StartTimer) ( unsigned char, unsigned char );
      extern int ( *FncOWASYS_StopTimer) ( unsigned char );
      extern int ( *FncOWASYS_FreeTimer) ( unsigned char );
      extern int ( *FncOWASYS_RestartTimer) ( unsigned char );

      extern int (*FncDIGIO_Enable_RS485)( char );
      extern int (*FncDIGIO_Enable_KLINE)( char );
      extern int (*FncDIGIO_Enable_Uart5)( unsigned char wValue );
      extern int (*FncDIGIO_Set_SD_Card)( unsigned char wValue );
      extern int (*FncDIGIO_Get_USB_A)( unsigned char *wValue );

      extern int (*FncRTUGetAD_V_IN)( float *);
      extern int (*FncRTUGetAD_VBAT_MAIN)( float *);
      extern int (*FncRTUGetAD_TEMP)( int *);
      extern int (*FncDIGIO_Set_CAN1_TX_Mode)( char );
      extern int (*FncDIGIO_Set_CAN2_TX_Mode)( char );
      extern int (*FncDIGIO_Set_CAN3_TX_Mode)( char );
      extern int (*FncDIGIO_Set_CAN4_TX_Mode)( char );
      extern int (*FncDIGIO_Switch_GPS_ON_OFF)( unsigned char);
      extern int (*FncDIGIO_Set_KLINE1_Threshold)( char );
      extern int (*FncDIGIO_Set_KLINE2_Threshold)( char );
      extern int (*FncRTUGetBatteryState)( unsigned char *wValue );
      extern int (*FncRTUGetBatteryChargeStatus)( unsigned char *wValue );
      extern int (*FncRTUSetBatteryChargeStatus)(  unsigned char wValue );
      
      
      //iButton
      extern int (*FncIBUTTON_Reset)(void);
      extern int (*FncIBUTTON_ReadByte)(unsigned char *);
      extern int (*FncIBUTTON_WriteByte)(unsigned char);
      extern int (*FncIBUTTON_ReadID)(unsigned char *);
      extern int (*FncIBUTTON_CfgInt)(void(*wHandler)(unsigned char *));
      extern int (*FncIBUTTON_RemoveInt)(void);
      
      extern int (*FncDIGIO_Set_VOUT)( unsigned char);
      extern int (*FncDIGIO_Get_VOUT_STATUS)( unsigned char *);
      extern int (*FncDIGIO_Get_PWR_FAIL)( unsigned char *);
      extern int (*FncDIGIO_Enable_Can)( char );
      
      //one wire
      extern int (*FncOW_Discover)( OneWireTable_t **, unsigned char *);
      extern int (*FncOW_SetUpdate)( void (*)(OneWireTable_t *, unsigned char, int), unsigned char);
      extern int (*FncOW_ResetUpdate)( void);

   #endif

#endif




