#ifndef _VBCCINLINE_I2C_H
#define _VBCCINLINE_I2C_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

LONG __ex_TestRequest(__reg("a6") struct I2CBase *, __reg("a0") STRPTR title, __reg("a1") STRPTR body, __reg("a2") STRPTR gadgets)="\tjsr\t-30(a6)";
#define ex_TestRequest(title, body, gadgets) __ex_TestRequest(I2CBase, (title), (body), (gadgets))

LONG __ex_TestRequest2A(__reg("a6") struct I2CBase *, __reg("a0") STRPTR title, __reg("a1") STRPTR body, __reg("a2") STRPTR gadgets, __reg("a3") APTR args)="\tjsr\t-36(a6)";
#define ex_TestRequest2A(title, body, gadgets, args) __ex_TestRequest2A(I2CBase, (title), (body), (gadgets), (args))

#if !defined(NO_INLINE_STDARG) && (__STDC__ == 1L) && (__STDC_VERSION__ >= 199901L)
__regsused("d0/d1/a0/a1/a3") LONG __ex_TestRequest2(__reg("a6") struct I2CBase *, __reg("a0") STRPTR title, __reg("a1") STRPTR body, __reg("a2") STRPTR gadgets, ...)="\tmovea.l\ta7,a3\n\tjsr\t-36(a6)";
#define ex_TestRequest2(title, body, ...) __ex_TestRequest2(I2CBase, (title), (body), __VA_ARGS__)
#endif

ULONG __ex_TestRequest3(__reg("a6") struct I2CBase *, __reg("a0") struct Hook * hook)="\tjsr\t-42(a6)";
#define ex_TestRequest3(hook) __ex_TestRequest3(I2CBase, (hook))

#endif /*  _VBCCINLINE_I2C_H  */
