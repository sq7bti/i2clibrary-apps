#ifndef _INCLUDE_PRAGMA_I2C_LIB_H
#define _INCLUDE_PRAGMA_I2C_LIB_H

#ifndef CLIB_I2C_PROTOS_H
#include <clib/i2c_protos.h>
#endif

#if defined(AZTEC_C) || defined(__MAXON__) || defined(__STORM__)
#pragma amicall(I2CBase,0x01e,ex_TestRequest(a0,a1,a2))
#pragma amicall(I2CBase,0x024,ex_TestRequest2A(a0,a1,a2,a3))
#pragma amicall(I2CBase,0x02a,i2c_AllocI2C(d0,a1))
#pragma amicall(I2CBase,0x030,i2c_FreeI2C())
#pragma amicall(I2CBase,0x036,i2c_SetI2CDelay(d0))
#pragma amicall(I2CBase,0x03c,i2c_InitI2C())
#pragma amicall(I2CBase,0x042,i2c_SendI2C(d0,d1,a0))
#pragma amicall(I2CBase,0x048,i2c_ReceiveI2C(d0,d1,a0))
#pragma amicall(I2CBase,0x04e,i2c_GetI2COpponent())
#pragma amicall(I2CBase,0x054,i2c_I2CErrText(d0))
#pragma amicall(I2CBase,0x05a,i2c_ShutDownI2C())
#pragma amicall(I2CBase,0x060,i2c_BringBackI2C())
#pragma amicall(I2CBase,0x066,ex_TestRequest3(a0))
#endif
#if defined(_DCC) || defined(__SASC)
#pragma  libcall I2CBase ex_TestRequest         01e a9803
#pragma  libcall I2CBase ex_TestRequest2A       024 ba9804
#pragma  libcall I2CBase i2c_AllocI2C           02a 9002
#pragma  libcall I2CBase i2c_FreeI2C            030 00
#pragma  libcall I2CBase i2c_SetI2CDelay        036 001
#pragma  libcall I2CBase i2c_InitI2C            03c 00
#pragma  libcall I2CBase i2c_SendI2C            042 81003
#pragma  libcall I2CBase i2c_ReceiveI2C         048 81003
#pragma  libcall I2CBase i2c_GetI2COpponent     04e 00
#pragma  libcall I2CBase i2c_I2CErrText         054 001
#pragma  libcall I2CBase i2c_ShutDownI2C        05a 00
#pragma  libcall I2CBase i2c_BringBackI2C       060 00
#pragma  libcall I2CBase ex_TestRequest3        066 801
#endif
#ifdef __STORM__
#pragma tagcall(I2CBase,0x060,ex_TestRequest2())
#endif
#ifdef __SASC_60
#pragma  tagcall I2CBase ex_TestRequest2        060 00
#endif

#endif	/*  _INCLUDE_PRAGMA_I2C_LIB_H  */
