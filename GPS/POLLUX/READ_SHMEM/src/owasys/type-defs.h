/*
 *
 * @file      type-defs.h
 * @brief     Definitions of the type structures
 * @author    PPI
 * @date      14/12/2013
 *
 * Copyright (c) 2013 ERICTEL
 * All rights reserved. Permission to use, modify or copy this software in whole or in part is
 * forbidden without prior, writen consent of the copyright holder.
 */
#ifndef TYPE_DEFS_H
#define TYPE_DEFS_H
#ifdef __cplusplus
extern "C" {
#endif
/***********************************************************
 *		System Includes
 ***********************************************************/
/***********************************************************
 *		User Includes
 ***********************************************************/
/***********************************************************
 *		Defines & Macros
 ***********************************************************/
#if defined(OWA3X)
   #include <owa3x/owcomdefs.h>
   #include <owa3x/owerrors.h>
   #define ROOT_PATH          "/home/"
#elif defined(PC)
   #ifndef NO_ERROR
   #define NO_ERROR  0
   #endif
   #define ROOT_PATH          "./"
   typedef int BOOL;
   #ifndef NULL
   #define NULL     0
   #endif

   #ifndef EOF
   #define EOF      (-1)
   #endif

   #ifndef FALSE
   #define FALSE     0
   #endif
/*******************************************************************************/
/*	NOTE:	No matter how we define 'TRUE', there's some possibility that 'TRUE'  */
/*			one one compiler won't be 'TRUE' on another.  This is only a problem  */
/*			for BOOL16 (e.g., files and messages between compilers).  Be careful. */
/*******************************************************************************/
   #ifndef TRUE
   #define TRUE     (!FALSE)
   #endif
#else
   #include <owasys/owcomdefs.h>
   #include <owasys/owerrors.h>
   #include <stdbool.h>
   #include <stdint.h>
   #ifndef BOOL
      typedef bool BOOL;
   #endif
   #ifndef BYTE
      typedef uint8_t BYTE;
   #endif
   #ifndef USHORT
      typedef uint16_t USHORT;
   #endif
   #ifndef WORD
      typedef uint16_t WORD;
   #endif
   #ifndef UINT16
      typedef uint16_t UINT16;
   #endif
   #ifndef ULONG
      typedef unsigned long ULONG;
   #endif
   #ifndef UINT
      typedef unsigned int UINT;
   #endif

   #define ROOT_PATH          "/"
   #define GCC_VERSION (__GNUC__ * 10000 \
   + __GNUC_MINOR__ * 100 \
   + __GNUC_PATCHLEVEL__)
#endif

#define ONE_SECOND   1

/* Store Info data */
#define MAX_STORE_SIZE        2048 * 8 //16384..Saving into native mode
#define MAX_STORE_INFO        2048
#define MAX_LINE_SIZE         255
#define STORE_HEAD_SIZE       (sizeof( unsigned long))

#define MIN_PER_DAY        1440

/* Copied from syslog */
#define LOG_EMERG 0 /* system is unusable */
#define LOG_ALERT 1 /* action must be taken immediately */
#define LOG_CRIT 2 /* critical conditions */
#define LOG_ERR  3 /* error conditions */
#define LOG_WARNING 4 /* warning conditions */
#define LOG_NOTICE 5 /* normal but significant condition */
#define LOG_INFO 6 /* informational */
#define LOG_DEBUG 7 /* debug-level messages */
#define  LOG_MIN     LOG_EMERG
#define  LOG_MAX     LOG_DEBUG

#if defined(OWA4X) || defined(OWA5X)
    #define  MAX_LOG_LINE   512
    #define  MAX_LOG_SIZE   2*1E6 // 2MB
#else
    #define  MAX_LOG_LINE   512
    #define  MAX_LOG_SIZE   128000
#endif

//Generic library errors
#define E_VOIDCOMM   -1
#define E_NOFILE     -2
#define E_NOJSON     -3 //Non-valid
#define E_NOTENABLED -4 //Not enabled
#define E_CMDSRV     -5 //Command not for this server

//Report definition
#define REPORT_BACKUP_PATH    ROOT_PATH"db/pollux.db"
#define REPORT_PATH           "/tmp/pollux.db"
#define REPORT_RAW_INT        "%ld\t%s\t%d\n"
#define REPORT_RAW_LNG        "%ld\t%s\t%ld\n"
#define REPORT_RAW_FLT        "%ld\t%s\t%f\n"
#define REPORT_RAW_DBL        "%ld\t%s\t%lf\n"
#define REPORT_RAW_LLN        "%ld\t%s\t%lld\n"

#define  MAX_EVENT_SIZE    255
#define  MAX_EVENTS_LEN    40
#define  MAX_SERVERS       20
#define  MAX_TAG_SIZE      32
#define  MAX_TAG_SIZE_XL   64 // Make sure to also change it in static libpollux
#define  MAX_EXP_SIZE      32
#define  MAX_RTDB_VARS     2048

#define  MAX_PHONE_LEN     20
#define  MAX_SMS_LEN       160

#define MAX_STRING_SIZE         255
#if defined(OWA4X) || defined(OWA5X)
    #define MAX_OBUS_STRING_SIZE    4096
#else
    #define MAX_OBUS_STRING_SIZE    2048
#endif
/**
 * Status of the server adq or module ...
 */
typedef enum _Status_t {
   ST_OFF,
   ST_INIT,
   ST_STARTING,
   ST_RUNNING,
   ST_ENDING
} Status_t;
//TODO: Check notifications....related to the main.c and usage

typedef enum {
   //Update / working
   APP_UPDATE,
   APP_REBOOT,
   //Net
   APP_SMS,
   APP_VOICE_CALL,
   //Generic
   APP_COMMAND,
   APP_JSON,
   APP_DBUS_SEND,
   APP_GET_WILDCARD,
   APP_SENDPOSITION,
   APP_SENDVALUE,
   APP_PUSHTOREDIS,
   APP_PERIODICVALUE,
   APP_GETREPORT,     //Get reported variables
   APP_RESTART
} cmds_e;

typedef enum{
   EV_RXVALUE = 0,   
   EV_RXPOSITION,
   EV_RXSMS,
   EV_TXVALUE,       
   EV_TXPOSITION,
   EV_CMD,
   EV_SET_CFG,
   EV_GET_CFG,
   EV_GETREPORT,
   EV_WILDCARD = 100
} events_e;
/* Struct to allocate structs with number of nodes*/
typedef struct {
   void *ptr; //Pointer to struct where data are stored
   int size; //sizeof every node
   int nodes; //Number of nodes to convert
} nonvolatile_t;

typedef enum _u_type {
   TYPE_BOOL,
   TYPE_SHORT,
   TYPE_USHORT,
   TYPE_LONG,
   TYPE_ULONG,
   TYPE_FLOAT
} u_type;

typedef struct _dval_t { //digital values
   unsigned char value; //Digital vale 0 or 1.
   unsigned long count; //Count of changes from 0 to 1
   unsigned long stamp; //Time stamp of the last change
   unsigned short timer; //Timer in seconds to do a pulse if !=0. Once pulse is executed timer will be 0 again
   unsigned char sent; //True if has sent the change. FALSE (0) if it hasn't
} dval_t;

typedef struct _aval_t { //analogue values
   float value; //Digital vale 0 or 1.
   unsigned long stamp; //Time stamp of the last change
   unsigned short timer; //Timer in seconds to do a pulse if !=0. Once pulse is executed timer will be 0 again
   unsigned char sent; //True if has sent the change. FALSE (0) if it hasn't
} aval_t;

typedef struct _gval_t { // General purposes values
   long long value; // value
   unsigned long stamp; //Time stamp of the last change
   unsigned short timer; //Timer in seconds to do a pulse if !=0. Once pulse is executed timer will be 0 again
   unsigned char sent; //True if has sent the change. FALSE (0) if it hasn't
} gval_t;

typedef enum _var_type_e { //Variable type
   T_NONE = 0,
   T_DIGITAL,
   T_ANALOGUE,
   T_INTEGER,
   T_BIG_LONG,
   T_DOUBLE,
   T_LONG
} var_type_e;

typedef enum _var_mode_e { //Variable writeable mode
   M_NONE = 0,
   M_READ,
   M_WRITE
} var_mode_e;

typedef struct _var_t { //Variable structure
   var_type_e type; //type of the variable, digital, analogue or other
   var_mode_e mode; //type of access mode: read, write 
   char *tag; //Pointer to the tag of the variable
   void *val; //Pointer to the value struct. Could be digital (dval_t) or analogue (aval_t)
} var_t;

/**
 * Server structs
 */
typedef struct _srv_param_t { //Parameters of the server to initialize it.
   int ( *cb_getVar) (char*, void*); //Gets Var from the module to the main activity since main activity could host it
   int ( *cb_command) (int, char *); //Ask for any operation hold on the main activity.
   int ( *cb_newvalue)( char*, void *); //Module Reports a new value to the main which will set on the system. The char * is the source module of data.
   int ( *cb_methodcall)( char**, void *); //Module calls a dbus method.
   char *filename; //Module configuration file if any.
   int shId; //Shared memory identifier
   //v2
   void ( *cb_log)   ( int, char*, ...);
} srv_param_t;

typedef struct {
   int nofvars; //Nof Vars in use
   int total; //Nof possible vars
   void *vars; //Variables local store...
} srv_var_t;

/**
 * The driver adquisition must implement these primitives or leave them voided. These make app, module or adq acts as an information server.
 * There is information generated by the module reported back to the main activity, and commands, incoming messages from external processes
 * to the module.
 * The module always attend it, not the main.
 * On init, the main app will give the configuration file. On initialization, the driver will return the loaded vars.
 */
typedef struct _srv_if { //Module server interface
   srv_var_t *srv_var;
   int ( *Init) (void *); /* Initialization: void * is the configuration pointer */
   int ( *Start) (); /* Start operation on threaded modules, or ends the initial configuration */
   int ( *Stop) (); /* Stops the execution but without quit from the thread */
   int ( *End) (); /* Ends adquisition driver */
   int ( *Run) (); /* Run once adquisition main thread. Only for non-thread adqs */
   int ( *EventHandler) (int, char*, void*); /* Info to send information from main to the module */
   Status_t(*Status) (); /* Status of the adq driver */
   int ( *Command) (int, char *); /* Command to the adq driver */
} srv_if;

typedef struct _srv_conf_t {
   char alias[ 50];
   char enabled; //Server enabled
   char file[ 255]; //Configuration file
   srv_if *adq;
   int shid; //Shared memory identifier
} srv_conf_t;

typedef struct _srv_t {
   srv_var_t *rtdb; //Pointer to values
   srv_conf_t *conf; //Pointer to configuration
} srv_t;

/*
 * Bearer commands
 */
typedef enum _b_cmd {
   BCMD_SEND, //Sends information
   BCMD_RECONNECT //Forces a new reconnection due to an IP change, or other
} b_cmd;

/**
 * Connection Interface. Class to handle connections bearer
 */
typedef struct _bearer_if {
   int ( *Init) (char *); /* Initialization: char * Path to the initialization file */
   int ( *Connect) (char *); /* Connect the bearer and stay as it's. Connection string is given */
   int ( *Disconnect) (); /* Disconnects from the server.  */
   int ( *End) (); /* Ends bearer and */
   Status_t(*Status) (); /* Status of the adq driver */
   int ( *Command) (b_cmd, char *); /* Command to the interface */
} bearer_if;

/**
 * Events structure to signal a value change of a variable....
 */
typedef struct {
   int event;
   char *args[ MAX_EVENT_SIZE];
} Events_t;

/* These values are related to sh_type_t struct in shmap.h*/
typedef enum {
   VAL_INT = 0,
   VAL_FLOAT = 1,
   VAL_BOOL = 2,
   VAL_LONG_LONG = 3,
   VAL_DOUBLE = 4,
   VAL_LONG = 5,
   VAL_POSITION = 100,
   VAL_SMS = 101,
   VAL_STR= 102
} val_type_t;

typedef   union {
   BOOL bVal;
   long iVal;
   float fVal;
   double dVal;
   long long llVal;
}Pvalue_t;

typedef struct {
   char DataValid;
   unsigned long LastValid;
   double Latitude; //Latitude     negative degrees means South
   double Longitude; //Longitude    negative degrees means East
   struct {
      double speed; //Speed in km/h
      double course; //Course over ground
   } Speed;
   int altitude; //Altitude in m.
   int satellites; //Number of available satellites
   double accuracy; //Horizontal accuracy
   char fix; //Fix type
} Pposition_t;

typedef struct {
   char phone[ MAX_PHONE_LEN];
   char text [ MAX_SMS_LEN];
} Psms_t;

typedef struct {
   char message[ MAX_OBUS_STRING_SIZE];
} Pstring_t;
/*********************************  **************************
 *		Private variables
 ***********************************************************/
/***********************************************************
 *		Functions definition
 ***********************************************************/


#ifdef __cplusplus
}
#endif
#endif /* TYPE_DEFS_H */
