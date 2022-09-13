/* Programmheader

	Name:		i2cset.c
	Main:		I2C
	Versionstring:	$VER: Test.c 1.1 (13.09.2022)
	Author:		BTI
	Distribution:	Freeware
	Description:	the I2C library test program

 1.0   13.09.22 : created initial code
*/

#include <stdio.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/i2c.h>
#include <libraries/i2c.h>

/* use global library, as this works for all compilers! */
struct I2CBase *I2CBase = 0;
//struct Library *I2CBase;

struct RDArgs *myrda;

#define TEMPLATE "A=Address/A,V=Value/A/M"
#define OPT_ADDR 0
#define OPT_VALUE 1
LONG result[2];

ULONG atoh(char c) {
	ULONG r;
	r = 0;
	if ((c <='9') && (c >= '0')) {
		r = c - '0';
	} else {
		r = 10 + c;
		if ((c <= 'F') && (c >= 'A'))
			r -= 'A';
		else
			r -= 'a';
	}
	return r;
}

ULONG stoi(STRPTR s) {
	ULONG r;
	r = 0;
	while(*s) {
		r <<= 4;
		if((*s == 'x') || (*s == 'X'))
			r = 0;
		else
			r += atoh((char)*s);
		++s;
	}
	return r;
}

UBYTE chip_addr, s, size, value, x;
UBYTE* buf;
ULONG error_code;
char** values;

int main(int argc, char **argv)
{
  /* Need to ask DOS for a RDArgs structure */
	if(!(myrda = (struct RDArgs *)AllocDosObject(DOS_RDARGS, NULL))) {
    PutStr("Usage: " TEMPLATE "\n");
    return 0;
	}

	size = 0;
	/* parse my command line */
	if(ReadArgs(TEMPLATE, result, myrda)) { //} && (strlen((char *)result[0]) > 0)) {
  	/*if(result[OPT_ADDR]) {*/
  		s = strlen((STRPTR)result[OPT_ADDR]);
      if((s == 2) || (strncmp((STRPTR)result[OPT_ADDR], "0x", 2) == 0) && (s == 4)) {
  	    chip_addr = stoi((STRPTR)result[OPT_ADDR]);
				values = (char **) result[OPT_VALUE];
				while(*values) {
					++values;
					++size;
				}
				s = 0;
				buf = AllocMem(size, MEMF_PUBLIC|MEMF_CLEAR);
				values = (char **) result[OPT_VALUE];
				while(*values) {
					value = stoi((STRPTR) *values);
/*        	printf("Write %d byte >%s< -> 0x%02X to chip at address >%s< -> 0x%02X\n",
												 s,   *values, value, (STRPTR)result[OPT_ADDR], chip_addr);*/
					++values;
					buf[s] = value;
					++s;
				}
  		} else {
		    PutStr("Usage: " TEMPLATE "\n");
      }
  		FreeDosObject(DOS_RDARGS, myrda);
    /*}*/
  } else {
		PutStr("Usage: " TEMPLATE "\n");
  }

  if(buf) {
    if(I2CBase = (struct I2CBase *) OpenLibrary("i2c.library", 39)) {
			error_code = SendI2C(chip_addr << 1, size, buf);
			if((error_code & 0xFF) == (chip_addr << 1)) {
        printf("0x%02X:", chip_addr);
        for(s = 0; s < size; s++)
          printf(" %02X", buf[s]);
        printf("\n");
      } else {
        printf("failed to write (0x%06X).\n", error_code);
      }
      CloseLibrary((struct Library *)I2CBase);
    } else {
      PutStr("Failed to open i2c.library\n");
      if(buf)
        FreeMem(buf, size);
      return 1;
    }
  } else {
    printf("Not enough memory to allocate the buffer\n");
    return 1;
  }

  return 0;
};
