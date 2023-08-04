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
//** Project:       owa4x_AN3
//** Description:
//**
//** Filename:      uart.h
//** Owner:         Owasys
//** Creation date: 15/12/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** V1.0.0   15/12/2017 First release                      owasys
//*********************************************************************


#ifndef __UART_H
   #define __UART_H

    #ifdef __UARTS_CPP
      static int         ReadUartDataFlag;
      static unsigned int        totalrxbytes=0;
      static unsigned int        totaltxbytes=0;

      static int OpenUart( char *wUart );
      static void *ReadUartData( void *args );

      int Enable_Uart5( void);
      int Test_Uart5( void);
      int Test_Uart1( void);
      int SetPort( char *port, int fd, struct termios *NewConfig, speed_t ParamBaud, int ParamLength, int ParamParity );
      void putdata( int fd, char *buffer, char bytesout );

   #else
      extern int Enable_Uart5( void);
      extern int Test_Uart5( void);
      extern int Test_Uart1( void);
      extern int SetPort( char *port, int fd, struct termios *NewConfig, speed_t ParamBaud, int ParamLength, int ParamParity );
      extern void putdata( int fd, char *buffer, char unsigned charsout );

   #endif

#endif //__UART_H

