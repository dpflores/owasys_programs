/* 
 * @File:   shmap.h
 * @Author: owzppi
 *
 * @date: 2014-01-10 13:24
 */

#ifndef SHMAP_H
#define	SHMAP_H
#ifdef __cplusplus
extern "C" {
#endif
   //* Shared memory includes
   #include <sys/types.h>
   #include <sys/ipc.h>
   #include <sys/shm.h>
   #include "type-defs.h"
   //Shared memory organization. Per key
   //SHM_ZONE
   //  |--(4) unsigned long size
   //  |--(50) sh_val_t[0]
   //  |------|--(1) sh_type_t      type   (int/float/bool)
   //  |------|--(1) sh_access_t    access (read/write)
   //  |------|--(32)tag            tag name (string)
   //  |------|--(8) unsigned long long val
   //  |------|--(4) unsigned long count     (counter of changes)
   //  |------|--(4) unsigned long  stamp
   //  | ...........
   //  | ...........
   //  |--(50) sh_val_t[size - 1]
   //  |------|--(1) sh_type_t      type   (int/float/bool)
   //  |------|--(1) sh_access_t    access (read/write)
   //  |------|--(32)tag            tag name (string)
   //  |------|--(8) unsigned long long val
   //  |------|--(4) unsigned long count     (counter of changes)
   //  |------|--(4) unsigned long  stamp
   
    /* These values are related to val_type_t struct in type-defs.h*/
   typedef enum _sh_type_t {
      SH_VAL_INT = 0,
      SH_VAL_FLOAT = 1,
      SH_VAL_BOOL = 2,
      SH_VAL_LONG_LONG = 3,
      SH_VAL_DOUBLE = 4,
      SH_VAL_LONG = 5
   }sh_type_t;
   typedef enum _sh_access_t {
      SH_ACCESS_NONE = 0,
      SH_ACCESS_READ,
      SH_ACCESS_WRITE
   }sh_access_t;
   typedef struct _sh_val_t {
      sh_type_t      type;
      sh_access_t    access;
      char           tag[ MAX_TAG_SIZE];
      union{
         BOOL        bVal;
         int         iVal;   
         long        lVal;
         float       fVal;
         double      dVal;
         long long   llVal;
      }val; //8
      //char           val[ 8];  //to put float, or long, long long --> 8 bytes
      unsigned long  count;   //Counter of changes....
      unsigned long  stamp;
   }sh_val_t;
   
   typedef struct _sh_t{
      int      id;      //Shared memory id
      key_t    key;     //Shared memory key
      size_t   size;    //Shared memory size
      void     *data;   //Shared memory ptr to the first item
   }sh_t;
   
   /* Till here */
   #define  SH_SIZE_INIT   sizeof( unsigned long)
   #define  SH_SIZE_VAR    sizeof( sh_val_t)
#ifdef SHMAP_C
   int  shm_Create     ( key_t key, size_t size, void **data);
   int  shm_End        ( key_t key, int id);
   int  shm_UpdateVal  (var_t *var, sh_val_t *item);
   const int sh_size[] = { 
      sizeof( int),        // SH_VAL_INT = 0,
      sizeof( float),      // SH_VAL_FLOAT = 1,
      sizeof( BOOL),       // SH_VAL_BOOL = 2,
      sizeof( long long),  // SH_VAL_LONG_LONG = 3,
      sizeof( double)      // SH_VAL_DOUBLE = 4
   };
#else
   extern int  shm_Create     ( key_t key, size_t size, void **data);
   extern int  shm_End        ( key_t key, int id);
   extern int  shm_UpdateVal  (var_t *var, sh_val_t *item);
   extern int  shm_UpdateShVal(void *var, sh_val_t *sh_val);
#endif
#ifdef __cplusplus
}
#endif
#endif	/* SHMAP_H */
