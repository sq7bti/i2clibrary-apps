#ifndef CLIB_I2C_PROTOS_H
#define CLIB_I2C_PROTOS_H


/*
**	$VER: i2c_protos.h 1.0 (20.06.2020)
**
**	C prototypes. For use with 32 bit integers only.
**
**	Copyright � 2020 Dirk Stoecker
**	All Rights Reserved
*/

#ifndef  LIBRARIES_I2C_H
#include <libraries/i2c.h>
#endif
#ifndef  UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif

BYTE AllocI2C(ULONG delaytype, STRPTR Name);
void FreeI2C(void);
ULONG SetI2CDelay(ULONG ticks);
void InitI2C(void);
ULONG SendI2C(ULONG addr, ULONG number, UBYTE * i2cdata);
ULONG ReceiveI2C(ULONG addr, ULONG number, UBYTE * i2cdata);
STRPTR GetI2COpponent(void);
STRPTR I2CErrText(ULONG errnum);
void ShutDownI2C(void);
BYTE BringBackI2C(void);

#endif	/*  CLIB_I2C_PROTOS_H  */
