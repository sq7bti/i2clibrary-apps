#ifndef _PROTO_I2C_H
#define _PROTO_I2C_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#if !defined(CLIB_I2C_PROTOS_H) && !defined(__GNUC__)
#include <clib/i2c_protos.h>
#endif

#ifndef __NOLIBBASE__
extern struct I2CBase *I2CBase;
#endif

#ifdef __GNUC__
#ifdef __AROS__
#include <defines/i2c.h>
#else
#include <inline/i2c.h>
#endif
#elif defined(__VBCC__)
#include <inline/i2c_protos.h>
#else
#include <pragma/i2c_lib.h>
#endif

#endif	/*  _PROTO_I2C_H  */
