/*
 * File      : sensorytypes.h
 * Purpose   : typedefs and code/data section definitions
 * Project   : any
 * Platform  : PC simulation of VPC and CSR code
 *
 * Copyright (C) 1995-2020 Sensory Inc., All Rights Reserved
 *
 * ******* SENSORY CONFIDENTIAL *************
 *
 *****************************************************************************
*/
#ifndef SENSORYTYPES_H_INCLUDED
#define SENSORYTYPES_H_INCLUDED

// define for Sensory logging feature
#define xSENSORY_LOGGING

#ifndef BOOL_S
  typedef unsigned char       BOOL_S;
#endif

// note: UINT, SINT these types are deprecated and only used in tsliceSimPC
#ifdef LEGACY_DEFINITIONS
  typedef unsigned char       UINT8;
  typedef unsigned short int  UINT16;
  typedef unsigned long int   UINT24;
  typedef unsigned long int   UINT32;
  typedef char                SINT8;
  typedef short int           SINT16;
  typedef long int            SINT24;
  typedef long int            SINT32;
#endif

typedef unsigned char       bool;
typedef unsigned char       b08;
typedef unsigned short int  b16;
typedef unsigned long int   b24;
typedef unsigned long int   b32;
typedef unsigned char       u08;
typedef unsigned short int  u16;
typedef unsigned long int   u24;
typedef unsigned long int   u32;
typedef unsigned long long  u48;
typedef unsigned long long  u64;
typedef char                s08;
typedef short int           s16;
typedef long int            s24;
typedef long int            s32;
typedef signed long long    s48;
typedef signed long long    s64;

// type needed when doing ptr + offset arithmetic to create ptr
typedef int                 INTFORPTR;
//typedef unsigned long int intptr_t;

// types needed for C nets and grammars
typedef const u16  __nn_t;
typedef const u16  __dnn_t;
typedef const u16  __gs_t;

#ifndef NULL
  #define NULL  (void *) 0
#endif

// needed for compatibility with VPC
#define UCODE
#define IRAM
#define IRAM1
#define RDATA const
#define NDATA const
#define CONST const

// limits
#ifndef UINT16_MAX
  #define UINT16_MAX (~(~0<<16))
#endif
#ifndef INT16_MAX
  #define INT16_MAX  (~(~0<<15))
#endif
#ifndef INT16_MIN
  #define INT16_MIN  (-32768)
#endif
#ifndef UINT32_MAX
  #define UINT32_MAX (0x00000000ffffffffUL)
#endif
#ifndef INT32_MAX
  #define INT32_MAX  (0x000000007fffffffL)
#endif
#ifndef INT32_MIN
  #define INT32_MIN  (0xffffffff80000000L)
#endif
//----------- platform-specific memory sizes

#define FFT_BUFFER_LEN  512
#define TMP_BUFFER_LEN  240  // 144 will skip first 96 samples of first frame

//----------- platform-specific options for generating debug info

#define SAVE_SAMPLES      0  // 1 = store microphone samples for review

//----------- debug output defs

#define Trace(x)

#define FDEBUG_FILE     "pcfrontend.dbg"
#define SDEBUG_FILE     "pcsearch.dbg"
#define NDEBUG_FILE     "pcnnet.dbg"

#define ALIGNED(x) __attribute__ ((aligned (x)))

#endif // SENSORYTYPES_H_INCLUDED
