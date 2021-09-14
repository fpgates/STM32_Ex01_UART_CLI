#ifndef _DEFINESS_H_
#define _DEFINESS_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define UI_AFD_TEST 0

/*******************************************************************************
* General types
*******************************************************************************/
#define VER_MAJOR	0x1
#define VER_MINOR	0x5B
#define BUILD_NUMBER 1

typedef const unsigned char     cu1_t;
typedef const unsigned short    cu2_t;
typedef const unsigned int      cu4_t;
typedef const unsigned long long cu8_t;

typedef unsigned char           u1_t;
typedef unsigned short          u2_t;
typedef unsigned int            u4_t;
typedef unsigned long long		u8_t;

#define UCHAR u1_t
#define USHORT u2_t
#define ULONG u4_t

typedef const char       cs1_t;
typedef char             s1_t;
typedef short            s2_t;
typedef int              s4_t;
typedef long long        s8_t;

#define CHAR u1_t
#define SHORT u2_t
#define LONG u4_t

typedef float                   f4_t;
//typedef float                 r4_t;
typedef double                  d8_t;
//typedef double                    r8_t;
typedef long double             ld_t;
//typedef long double               r10_t;
//typedef long double               r12_t;
//typedef long double               r16_t;

/*******************************************************************************
* BOOL type and accompanying values
*******************************************************************************/
#if 0
typedef enum bool_e
{
    BOOL_FALSE = 0,
    BOOL_TRUE  = 1
} bool_td;
#endif
/*******************************************************************************
* Definition of NULL pointer value
*******************************************************************************/
#ifdef NULL
#undef NULL
#endif

#ifdef  __cplusplus
#define NULL            0
#else
#define NULL            ((void*) 0)
#endif

/*******************************************************************************
* maximum values that can be held by unsigned/signed data types (1,2,4 Bytes)
*******************************************************************************/
#define MAX_U1  255
#define MAX_U2  65535
#define MAX_U4  4294967295

#define MIN_S1  -128
#define MAX_S1  127
#define MIN_S2  -32768
#define MAX_S2  32767
#define MIN_S4  -2147483648
#define MAX_S4  2147483647

/*******************************************************************************
* ErrCode_t type and accompanying values
*******************************************************************************/
//#define _SYSTEM_BASE                 0x1000
//#define _SPI_ERR_BASE                0x3000
//s#define _GENBASE                     0x4000


#define ERR_SUCCESS        (0x00000000)
#define ERR_WARNING        (0x81000000 + (__LINE__ & 0xFFFFFF))
#define ERR_FAILED         (0x82000000 + (__LINE__ & 0xFFFFFF))
#define ERR_READ_REGISTER  (0x83000000 + (__LINE__ & 0xFFFFFF))
#define ERR_WRTIE_REGISTER (0x84000000 + (__LINE__ & 0xFFFFFF))
#define ERR_UNAVAILABLE    (0x85000000 + (__LINE__ & 0xFFFFFF))
#define ERR_UNKNOWN_ID     (0x86000000 + (__LINE__ & 0xFFFFFF))
#define ERR_CHECKSUM       (0x87000000 + (__LINE__ & 0xFFFFFF))
#define ERR_TIMEOUT        (0x88000000 + (__LINE__ & 0xFFFFFF))
#define ERR_INVALID_PARAM  (0x89000000 + (__LINE__ & 0xFFFFFF))
#define ERR_INVALID_CMD    (0x8A000000 + (__LINE__ & 0xFFFFFF))
#define ERR_VERSION        (0x8B000000 + (__LINE__ & 0xFFFFFF))

#if 0
enum ERROR_Status_e
{
	ERR_SUCCESS	= 0,
	ERR_WARNING,
	ERR_FAILED,
	ERR_READ_REGISTER,
	ERR_WRTIE_REGISTER,
	ERR_UNAVAILABLE,
	ERR_UNKNOWN_ID,
	ERR_CHECKSUM,
	ERR_TIMEOUT,
	ERR_INVALID_PARAM,
	ERR_VERSION
};
#endif

typedef unsigned short ErrCode_t;


/*******************************************************************************
* MIN/MAX/ABS macros
*******************************************************************************/

#define MIN(a,b)            ((a<b)?(a):(b))
#define MAX(a,b)            ((a>b)?(a):(b))
#define ABS(x)              ((x>0)?(x):(-x))

/*******************************************************************************
* Constants
*******************************************************************************/
#define PHI     3.14159265359

/*******************************************************************************
* Sleep (mili sec)
*******************************************************************************/
#ifndef msleep //warning by mskang
#define msleep(msec) usleep(msec*1000)
#endif

typedef enum SYS_STATUS_e {
    ER_SUCCESS = 0,
    ER_FAIL,
    ER_RESERVED
} SYS_STATUS_t ;

typedef union Word2Bytes_u
{
	struct
	{
		u4_t bf8_B0 :8;
		u4_t bf8_B1 :8;
		u4_t bf8_B2 :8;
		u4_t bf8_B3 :8;
	};

	u4_t u4_Value;
} Word2Bytes_t;


#define RES_RANGE(value,x,y) (value < x+y && value > x-y)


#define UNKNOWN_READ 0
#define UNKNOWN_BASE 0

#define SWAP_2Byte(s) \
    (((((s) & 0xff) << 8) | (((s) >> 8) & 0xff)))

#define SWAP_4Byte(l) \
    ( ((((l) & 0xff000000) >> 24) | \
     (((l) & 0x00ff0000) >> 8)  | \
  (((l) & 0x0000ff00) << 8)  | \
  (((l) & 0x000000ff) << 24)))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*DEFINES_H_*/


