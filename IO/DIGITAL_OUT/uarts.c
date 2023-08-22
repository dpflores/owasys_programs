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
//** Filename:      uart.cpp
//** Owner:         Owasys
//** Creation date: 15/12/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** V1.0.0   15/12/2017 First release                      owasys
//*********************************************************************

#define __UARTS_CPP

//-----------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------//
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

//-----------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------//
#include <owa4x/owerrors.h>
#include <owa4x/owcomdefs.h>
#include "owa4x_AN3.h"
#include "LoadLibs.h"
#include "uarts.h"

//-----------------------------------------------------------------//
//Defines
//-----------------------------------------------------------------//
#define UART1        "/dev/ttyO1"
#define UART5        "/dev/ttyO5"
#define TXBUFSIZE    256


static struct termios oldtio;

//-----------------------------------------------------------------//
//Global functions
//-----------------------------------------------------------------//

static int OpenUart( char *wUart )
{
   int            fd;
   struct termios newtio;
   int            retval;

   fd = open(wUart, O_RDWR | O_NOCTTY | O_NONBLOCK);
   if( fd < 0) {
      printf("open %s error %s\n", wUart, strerror(errno));
      return -1;
   }

   retval = tcgetattr(fd, &oldtio);  //Get: c_iflag       input modes 
                                     //     c_oflag       output modes 
                                     //     c_cflag       control modes 
                                     //     c_lflag       local modes 
                                     //     c_cc[NCCS]    control chars 
   if( retval < 0 ) {
      printf("tcgetattr error %s\n", strerror(errno));
      return -1;
   }

   newtio = oldtio;
   
   if( SetPort(wUart, fd, &newtio, B115200, CS8, IGNPAR) < 0 ) { // Set linux port interface to new baudrate.
      return -1;
   }
   return fd;
}

static void *ReadUartData( void *args )
{
   int            n;
   int            fd = *(int*)args;
   int            max_fd=0;
   fd_set         input;
   struct timeval timeout;
   char           buffer[50];
   char           auxbuffer[50];
   int            rxbytes=0;

   FD_ZERO(&input);
   FD_SET(fd, &input);
    
   max_fd = fd + 1;

   memset(auxbuffer,0,50);
   while(ReadUartDataFlag) {
      // Initialize the timeout structure 
      timeout.tv_sec  = 0;
      timeout.tv_usec = 500000;
      // Do the select 
      n = select(max_fd, &input, NULL, NULL, &timeout);

      if( ReadUartDataFlag == FALSE )
         continue;
       
      // See if there was an error 
      if( n < 0 ) {
         printf("select failed %s\n", strerror(errno));
      } else if (n == 0) {
//         printf("TIMEOUT\r\n");
      } else {
//         printf("HAY DATOS\r\n");
         // We have input 
         if( FD_ISSET(fd, &input) ) {
            memset(buffer, 0, 50);
            rxbytes = read(fd,buffer,50);
            totalrxbytes += rxbytes;
//            if( totalrxbytes == strlen(msgtotx) ) {
            if( (buffer[rxbytes-1] == '\n') || (buffer[rxbytes-2] == '\r') ) {
               if( auxbuffer[0] != 0 ) {
                  strcat(auxbuffer, buffer); 
               }   
               else {
                  strncpy(auxbuffer, buffer, rxbytes); 
               }
               printf(" RX %d bytes FD(%d)=%s\n", strlen(auxbuffer), fd, auxbuffer);
               totalrxbytes = 0;
               memset(auxbuffer,0,50);
            }
            else {
               //save partial message
               if( rxbytes > 0) {
                  if( auxbuffer[0] == 0 ) {
                     strncpy(auxbuffer, buffer, rxbytes); 
                  } 
                  else {
                     strcat(auxbuffer, buffer);  
                  }
               }
            }
         }
      }
      FD_ZERO(&input);
      FD_SET(fd, &input);
   }
   pthread_exit( NULL);
}

int Enable_Uart5( void)
{
   int ReturnCode = NO_ERROR;
   unsigned char  value;
   char  BufKey[6];

   printf("Enter UART5 (0:Disable, 1:Enable):");
   getEntry(BufKey);
   value = atoi(BufKey);
   ReturnCode = (*FncDIGIO_Enable_Uart5)(value);
   if( ReturnCode == NO_ERROR ) {
      printf(" UART5 %s OK\r\n", value ? "Enabled" : "Disabled" );
   } else {
      printf("Error %d setting UART5\r\n", ReturnCode);
   }
   return ReturnCode;
}

int Test_Uart5( void)
{
   int         j;                                  
   int         Uart5FD;
   pthread_t   uart5Rxthread;
   char        TestMsg[50];

   printf("Enter test message:");
   getEntry(TestMsg);
   strcat(TestMsg, "\r\n");
   totaltxbytes = strlen(TestMsg);

   Uart5FD = OpenUart( (char *)UART5);
   if( Uart5FD < 0 )
      return -1;

   ReadUartDataFlag = TRUE;
   //create reception thread
	pthread_create(&uart5Rxthread, NULL, ReadUartData, &Uart5FD);

   for(j=0;j<1;j++) {                                    
      putdata(Uart5FD, TestMsg, totaltxbytes);  // send msg
      (*Fncusecsleep)(1,0);
   }
   ReadUartDataFlag = FALSE;
   pthread_join(uart5Rxthread, NULL);
	tcsetattr(Uart5FD, TCSANOW, &oldtio);
	tcflush(Uart5FD, TCIOFLUSH);
   close( Uart5FD);
   return 0;
}

int Test_Uart1( void)
{
   int         j;                                  
   int         Uart1FD;
   pthread_t   uart1Rxthread;
   char        TestMsg[50];

   printf("Enter test message:");
   getEntry(TestMsg);
   strcat(TestMsg, "\r\n");
   totaltxbytes = strlen(TestMsg);

   Uart1FD = OpenUart( (char *)UART1);
   if( Uart1FD < 0 )
      return -1;

   ReadUartDataFlag = TRUE;
   //create reception thread
	pthread_create(&uart1Rxthread, NULL, ReadUartData, &Uart1FD);

   for(j=0;j<1;j++) {                                    
      putdata(Uart1FD, TestMsg, totaltxbytes);  // send msg
      (*Fncusecsleep)(1,0);
   }
   ReadUartDataFlag = FALSE;
   pthread_join(uart1Rxthread, NULL);
	tcsetattr(Uart1FD, TCSANOW, &oldtio);
	tcflush(Uart1FD, TCIOFLUSH);
   close( Uart1FD);
   return 0;
}

int SetPort( char *port, int fd, struct termios *NewConfig, speed_t ParamBaud, int ParamLength, int ParamParity )
{
   int  ReturnCode = 0;

//   NewConfig->c_cflag |= ParamBaud | ParamLength | CLOCAL | CREAD | CRTSCTS;
   NewConfig->c_cflag |= ParamBaud | ParamLength | CLOCAL | CREAD;
   NewConfig->c_iflag = ParamParity;
//   NewConfig->c_iflag |= ParamParity;
//   NewConfig->c_iflag &= ~(IXON | IXOFF | IXANY);
	NewConfig->c_oflag = 0;    // no output modes
	NewConfig->c_lflag = 0;    // no canonical, no echo, ...
   NewConfig->c_cc[VMIN] = 0;
  	NewConfig->c_cc[VTIME] = 0;

	ReturnCode = cfsetospeed(NewConfig, ParamBaud);
	if (ReturnCode < 0) {
      printf("Could not set output speed!\n");
		return -1;
	}
	ReturnCode = cfsetispeed(NewConfig, ParamBaud);
	if (ReturnCode < 0) {
      printf("Could not set input speed!\n");
		return -1;
	}
	tcsetattr(fd, TCSANOW, NewConfig);
	tcflush(fd, TCIOFLUSH);

   printf(" %s configured succesfully, FD(%d).\n", port, fd);
	return 0;
} 

void putdata( int fd, char *buffer, char bytesout )
{
   int      i;                                  
   ssize_t  written;

   printf(" TX %d bytes to FD(%d):%s\r\n", bytesout, fd, buffer);
   for(i=0; i < bytesout; i++) {             
      written = write( fd, &buffer[i], 1);
      if( written <= 0) {
         printf("ERROR TX(%d), FD(%d)\r\n", buffer[i], fd);
      }
   }
}

