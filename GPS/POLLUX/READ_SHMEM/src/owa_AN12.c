
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
//** Description: shared memory access application note
//**
//** Filename:      owa_AN12.c
//** Creation date: 19/06/2017
//**
//*********************************************************************
//******************** Revision history *******************************
//** Revision date       Comments                           Responsible
//** -------- ---------- ---------------------------------- -----------
//** P1A      19/06/2017 First release                      Owasys
//*********************************************************************
#define __OWA_AN12_C
//-----------------------------------------------------------------//
//System Includes
//-----------------------------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <owasys/pollux/shmap.h>
#include <owasys/pollux/type-defs.h>

//-----------------------------------------------------------------//
//User Includes
//-----------------------------------------------------------------//
#include "owa_AN12.h"

//-----------------------------------------------------------------//
//Defines
//-----------------------------------------------------------------//
#define TAG_SIZE MAX_TAG_SIZE
//-----------------------------------------------------------------//
//Macros
//-----------------------------------------------------------------//
//-----------------------------------------------------------------//
//External variables
//-----------------------------------------------------------------//
//-----------------------------------------------------------------//
//External functions
//-----------------------------------------------------------------//
//-----------------------------------------------------------------//
//Private variables
//-----------------------------------------------------------------//

//-----------------------------------------------------------------//
//Private funcions
//-----------------------------------------------------------------//
//User Variables

//-----------------------------------------------------------------//
// Function: main()
// Input Params:
//    -
// Output Params:
//    Result of the program
// Description:
//    Main function to work with GSM library
//-----------------------------------------------------------------//
int main( int argc, char *argv[])
{
	int MemoryId;
	char tag[ TAG_SIZE];

	printf( "OWASYS--> Starting owa_AN12 Test Application %s (%s,%s)\n",
					APP_VERSION, __DATE__ , __TIME__);

	if(argc >= 2) {
		bzero( tag, TAG_SIZE);
		MemoryId = strtol( argv[1], NULL, 10);
		if( argc == 3)
			strncpy( tag, argv[2], TAG_SIZE);
		shm_read( MemoryId, tag);
	} else {
		printf("Usage: owasys-an12 IdMemory\n");
		printf("       owasys-an12 IdMemory Tag\n");
	}
	printf( "OWASYS--> OK Ending the owasys-an12\n");
	exit( 0);
}

int shm_read( int shm_id, char *tag){
   int id, i;
   unsigned long nofdata;
   void *data, *ptr;
   sh_val_t *val;
   id = shmget( shm_id, sizeof( unsigned long), 0644);
   if( id >= 0){
      data = shmat( id, 0, 0);
      memcpy( &nofdata, data,  sizeof( unsigned long));
      printf( "Nof data: %ld\n", nofdata);
      if( data != NULL){
         if( shmdt( (const void *) data))
            printf("Error on shmdt: %d\n", errno);
      }
      //printf( "Asking for: %ld\n", SH_SIZE_INIT + nofdata );
      id = shmget( shm_id, SH_SIZE_INIT + ( nofdata * SH_SIZE_VAR), 0644);
      if( id >= 0){
         data = shmat( id, 0, 0);
         ptr = data;
         ptr += SH_SIZE_INIT;
         val = ( sh_val_t *) ptr;
			printf( WHTBB" %-6s|%-32s|%-5s|%-19s|%-8s|%-21s|"RESET"\n"," Id"," Tag"," Type"," Value"," Count"," Stamp");
         for( i = 0; i < nofdata; i++, val++){
				if( strlen( tag)){
					if ( !streq( val->tag, tag)){ //Do not print the 
						continue;
					}
				}
				print_shared_var( val, i);
         }
         if( shmdt( (const void *) data))
            printf( "Error on shmdt: %d\n", errno);
      } else {
         printf( "Error on shmget: %d\n", errno);
      }
   } else{
      printf( "No shared memory detected: %d\n ",shm_id);
   }
   return 0;
}
//Function to print every line with different format depending on the id odd or even

void print_shared_var( sh_val_t *val, int i){
	char stamp[ 32];
	if( strlen( val->tag)){
		if( i % 2)
			printf( WHTBB" [%03d] | %-31s",i,val->tag);
		else
			printf( WHT" [%03d] | %-31s",i,val->tag);
	} else {
		printf( " [%03d] | %-31s",i,"-");
	}

	if( val->type == SH_VAL_FLOAT){
		printf( "|%-5s| %*.8f ", " F ", 17, val->val.fVal);
	} else if( val->type == SH_VAL_DOUBLE){
		printf( "|%-5s| %*.8lf ", " D ", 17, val->val.dVal);
	} else if( val->type == SH_VAL_LONG_LONG){
		printf( "|%-5s| %*lld ", " LL", 17,val->val.llVal);
	} else if( val->type == SH_VAL_LONG){
		printf( "|%-5s| %*ld ", " L ", 17,val->val.lVal);
	} else {
		printf( "|%-5s| %*d ", " I ", 17, val->val.iVal);
	}
	printf( "| %*ld ", 6, val->count);
	bzero( stamp, 32);
	if( val->stamp > 0)
		strftime( stamp, 32, "%Y-%m-%d %H:%M:%S", localtime( &val->stamp));
	else
		strcpy( stamp, "-");
	printf( "| %-19s |"RESET"\n", stamp);
}

time_t get_base_time( void *ptr, int nofdata){
	time_t base = 0;
	int i;
	for( i = 0; i < nofdata; i++, ptr += SH_SIZE_VAR){
		sh_val_t *val = ( sh_val_t *) ptr;
		if( streq( val->tag, "beat")){
			base = val->val.llVal;
			break;
		}
	}
	return base;
}