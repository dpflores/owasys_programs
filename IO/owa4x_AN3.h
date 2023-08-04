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
//** Filename:       owa4x_AN3.h
//** Owner:          Owasys
//** Creation date:  15/12/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** See versions.txt
//*********************************************************************

#ifndef __OWA3X_AN3_H
   #define __OWA3X_AN3_H

//-----------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------//
   #include <stdlib.h>
   #include <signal.h>
   #include "owa4x/owcomdefs.h"
   #include "owa4x/pm_messages.h"
   #include "owa4x/IOs_ModuleDefs.h"
   #include "owa4x/RTUControlDefs.h"


//-----------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------//

//-----------------------------------------------------------------//
//Defines
//-----------------------------------------------------------------//

//   #define IO_(X) X
//   #define PARM_(X) X
//   #define VAR_(X) X
//   #define INFO_(X) X

#define  PARM_(X)
#define  IO_(X)
#define  VAR_(X)
#define  INFO_(X)

#define LIBRTU       "/lib/libRTU_Module.so"
#define LIBIO        "/lib/libIOs_Module.so"

#define UART_RS485   "/dev/ttyO2"

#define SW_VERSION   "0.0.7"

   //Commands
#define CMD_SET_LED_SW0        "set yellowled\0"
#define CMD_SET_LED_SW1        "set greenled\0"
#define CMD_SET_LED_SW2        "set redled\0"
#define CMD_SET_LED_SW3        "set orangeled\0"
#define CMD_SET_ADC_RANGE      "set adc_range\0"

#define CMD_GET_ANA0           "get ana0\0"
#define CMD_GET_ANA1           "get ana1\0"
#define CMD_GET_ANA2           "get ana2\0"
#define CMD_GET_ANA3           "get ana3\0"

#define CMD_GET_IN             "get input\0"
#define CMD_GET_ALL_IN         "get all input\0"
#define CMD_SET_OUT            "set out\0"
#define CMD_SET_ALL_OUT        "set all out\0"
#define CMD_CFG_int            "cfg int\0"
#define CMD_GET_intS           "get ints\0"
#define CMD_REMOVE_int         "rem int\0"
#define CMD_TEST_TIMER         "test timer\0"
#define CMD_ENABLE_485         "enable 485\0"
#define CMD_RX_485             "rx 485\0"
#define CMD_TX_485             "tx 485\0"
#define CMD_ENABLE_KLINE       "enable kline\0"
#define CMD_TEST_UART1         "test uart1\0"
#define CMD_ENABLE_UART5       "enable uart5\0"
#define CMD_TEST_UART5         "test uart5\0"
#define CMD_SET_SD             "set sd"
#define CMD_GET_USB_A          "get usb_a"

#define CMD_GET_VIN	       "get vin\0"
#define CMD_GET_VBAT           "get vbat\0"
#define CMD_GET_TEMP           "get temp\0"
#define CMD_ENABLE_IBUTTON     "enable ibutton\0"
#define CMD_DISABLE_IBUTTON    "disable ibutton\0"
#define CMD_READ_IBUTTON       "read ibutton\0"
#define CMD_READ_OWTEMP       "read owtemp\0"
#define CMD_SET_VOUT	       "set vout\0"
#define CMD_GET_VOUT	       "get vout\0"
#define CMD_GET_PWR_FAIL       "get pwr_fail\0"
#define CMD_ENABLE_CAN         "enable can\0"
#define CMD_DIS_OW             "discover ow\0"
#define CMD_UPDATE_OW          "update ow\0"
#define CMD_RESET_OW           "reset ow\0"
#define CMD_CAN1TX_MODE        "can1tx mode"
#define CMD_CAN2TX_MODE        "can2tx mode"
#define CMD_CAN3TX_MODE        "can3tx mode"
#define CMD_CAN4TX_MODE        "can4tx mode"
#define CMD_SWITCH_GPS         "switch gps"
#define CMD_KLINE1_TH          "kline1 th"
#define CMD_KLINE2_TH          "kline2 th"
#define CMD_BAT_STAT           "get bat-stat"
#define CMD_GET_BAT_CH         "get bat-charge"
#define CMD_SET_BAT_CH         "set bat-charge"

#define CMD_QUIT               "quit\0"

#define IBUTTON_SKIP_ROM   0xCC
#define IBUTTON_CONVERT_T  0x44
#define IBUTTON_READ_MEM   0xBE
#define IBUTTON_DS1820_MEMSIZE   9
#define DS18S20   0x10
#define DS18B20   0x28
#define DS1822    0x22

   #ifdef __OWA3X_AN3_CPP
      static int FD_485 = -1;
      static char CheckMsg[7] = { 0xCC,   //BEGIN_char
                                  0x02,   //destinationDevice
                                  0X80,   //CHECK_CONNECTION_COMMAND
                                  0x01,   //myaddress
                                  0xDD,   //END_char
                                  0x0D,
                                  0x00 };

      static char StatusDevice[5][16] = {
				"EMPTY",
				"UPDATED",
				"NEW",
				"REMOVE",
				"PENDING"
		};

      static struct termios oldtio, newtio;

      void WriteLog( const char *format, ... );
      time_t GetCurTime( time_t *p );
      void getEntry( char *strEntry );
      static int Config_Interrupts( void);
      static int Get_Interrupts( void);
      static int Remove_Interrupts( void);
      static int Get_Dig_In( void);
      static int Get_All_Dig_In( void);
      static int Set_Dig_Out( void);
      static int Set_All_Dig_Out( void);
      static void InputIntHandler( input_int_t wInState);
      static int Test_Timers( void);
      static void TimerHandler( unsigned char nTimer);
      static int Rx_RS485( unsigned char wResp);
      static int Tx_RS485( void);
      static int OpenUart485( void);
      static int Set_Adc_Range( void);
      static int Enable_RS485( void);
      static int Enable_KLine( void);
      static int Set_SD_Card( void);
      static int Get_USB_A( void);

      static int GetVin( void);
      static int GetVbat( void);
      static int GetTemp( void);
      static void iButtonInterruptHandler(unsigned char *pData);
      static int Set_VOUT( void);
      static int Get_VOUT_STATUS( void);
      static int Get_PWR_FAIL( void);
      static int EnableCan( void);
      static int DiscoverOneWire( void);
      static int UpdateOneWire( void);
      static int ResetUpdateOneWire( void);
      static void OwUpdateInterruptHandler( OneWireTable_t *pDevices, unsigned char, int);
      static int Set_CAN_TX_Mode( char number);
      static int Switch_GPS( void);
      static int Set_KLINE1_Threshold( void);
      static int Set_KLINE2_Threshold( void);
      static int Get_Bat_Stat( void);
      static int Get_Bat_Charge_Stat( void);
      static int Set_Bat_Charge_Stat( void);

   #else
      extern void WriteLog( const char *format, ... );
      extern void getEntry( char *strEntry );

   #endif

#endif
