/* Programmheader

	Name:		i2cget.c
	Main:		I2C
	Versionstring:	$VER: Test.c 1.1 (13.09.2022)
	Author:		BTI
	Distribution:	Freeware
	Description:	the I2C library test program

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

#define TEMPLATE "A=Address/A,L=Length/N,D=Decimal/S"
#define OPT_ADDR 0
#define OPT_LENGTH  1
#define OPT_DECIMAL  2
LONG result[3];

UBYTE atoh(char c) {
	UBYTE r;
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

UBYTE stoi(STRPTR s) {
	UBYTE r;
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

UBYTE chip_addr, s, size;
UBYTE *buf;
ULONG error_code;
BOOL decimal;

int main(int argc, char **argv)
{
  /* Need to ask DOS for a RDArgs structure */
	if(!(myrda = (struct RDArgs *)AllocDosObject(DOS_RDARGS, NULL))) {
    PutStr("Usage: " TEMPLATE "\n");
    return 0;
	}

	/* by default print out bytes in HEX 0x%02X */
	decimal = 0;
	/* parse my command line */
	if(ReadArgs(TEMPLATE, result, myrda) && (strlen((char *)result[0]) > 0)) {
  	if(result[OPT_ADDR]) {
  		s = strlen((STRPTR)result[OPT_ADDR]);
      if((s == 2) || (strncmp((STRPTR)result[OPT_ADDR], "0x", 2) == 0) && (s == 4)) {
  	    chip_addr = stoi((STRPTR)result[OPT_ADDR]);
  			//printf("Chip address Specified : >%s<, len=%d -> 0x%02X\n", (STRPTR)result[OPT_ADDR], strlen((STRPTR)result[OPT_ADDR]), chip_addr);
  			if(result[OPT_LENGTH]) {
					if(result[OPT_DECIMAL])
						decimal = 1;
  				size = *((ULONG*)(result[OPT_LENGTH]));
          //printf("Read %d bytes from address >%s< -> 0x%02X\n", size, (STRPTR)result[OPT_ADDR], chip_addr);
        }
  		} else {
		    PutStr("Usage: " TEMPLATE "\n");
      }
  		FreeDosObject(DOS_RDARGS, myrda);

    }
  } else {
    PutStr("No arguments\n");
  }

  if(buf = AllocMem(size, MEMF_PUBLIC|MEMF_CLEAR)) {
    if(I2CBase = (struct I2CBase *) OpenLibrary("i2c.library", 39)) {
			printf("0x%02X:", chip_addr);
			error_code = ReceiveI2C(chip_addr << 1, size, buf);
			if((0xFF & error_code) == size) {
        for(s = 0; s < size; s++)
					if(decimal)
						printf(" %d", buf[s]);
					else
						printf(" 0x%02X", buf[s]);
        printf("\n");
      } else {
        printf(" failed to read (0x%06X).\n", error_code);
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
