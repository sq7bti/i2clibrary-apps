/* Programmheader

	Name:		Test.c
	Main:		I2C
	Versionstring:	$VER: Test.c 1.1 (21.09.2002)
	Author:		SDI
	Distribution:	Freeware
	Description:	the I2C library test program

 1.0   25.06.00 : created that I2C library code
 1.1   21.09.02 : error fixes
*/

#include <stdio.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/i2c.h>
#include <libraries/i2c.h>

/* use global library, as this works for all compilers! */
struct I2CBase *I2CBase = 0;
//struct Library *I2CBase;

UWORD number = 0;
UBYTE buf[3] = { 0x00, 0x00, 0x00 };
ULONG error_code;
unsigned short temperat;
UBYTE chip_addr, s;
UWORD size = 1;
/*float thyst;*/
ULONG thyst_fp;
int argNo;

/* My custom RDArgs */
struct RDArgs *myrda;

#define TEMPLATE "A=Address/A,T=Thyst"
#define OPT_ADDR 0
#define OPT_THYST 1
LONG result[2];

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

/* fixed point notation U16Q8 */
ULONG stof(STRPTR s) {
	ULONG prec = 10;
	ULONG r = 0;
	UBYTE neg = 0;
	while(*s) {
		if((*s == '.') || (*s == ',')) {
			++s;
			break;
		} else {
			if((*s) == '-') {
				neg = 1;
			} else {
				r *= 10;
				r += atoh(*s) << 8;
//				printf("next digit: %c -> 0x%04lx\n", *s, r);
			}
		}
		++s;
	}
	printf("decimal point: 0x%04lx\n", r);
	while(*s && prec) {
		r += (atoh(*s) << 8) / prec;
//		printf("next digit: %c", *s);
//		printf(" -> 0x%04x", atoh(*s) << 8);
//		printf(" -> 0x%04lx", (atoh(*s) << 8) / prec);
//		printf(" -> 0x%04lx\n", r);
		prec *= 10;
		++s;
	}
	return neg?(~r + (1<<8)):r;
}

ULONG stoi(STRPTR s) {
	ULONG r;
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

int main(int argc, char **argv)
{
  I2CBase = (struct I2CBase *) OpenLibrary("i2c.library", 39);

	chip_addr = 0x48;

  if(I2CBase) {
    if (myrda = (struct RDArgs *)AllocDosObject(DOS_RDARGS, NULL)) {
  	/* parse my command line */
  		if (ReadArgs(TEMPLATE, result, myrda) && (strlen((char *)result[0]) > 0)) {
  			if(result[OPT_ADDR]) {
  				s = strlen((STRPTR)result[OPT_ADDR]);
  				if((s == 1) || (s == 2) || (strncmp((STRPTR)result[OPT_ADDR], "0x", 2) == 0) && (s == 4)) {
						if((s == 1) && stoi((STRPTR)result[OPT_ADDR]))
  							chip_addr += stoi((STRPTR)result[OPT_ADDR]);
						else
							chip_addr = stoi((STRPTR)result[OPT_ADDR]);
  					printf("Chip address Specified : >%s<, len=%d -> 0x%02X\n", (STRPTR)result[OPT_ADDR], strlen((STRPTR)result[OPT_ADDR]), chip_addr);
  				}
  				if(result[OPT_THYST]) {
  					s = strlen((STRPTR)result[OPT_THYST]);
  					size = 3;
  					/*thyst = atof((STRPTR)result[OPT_THYST]);*/
  					thyst_fp = stof((STRPTR)result[OPT_THYST]);
  					/*printf("Register address Specified : >%s<, len=%u -> %f -> 0x%04lx\n", (STRPTR)result[OPT_THYST], s, thyst, thyst_fp);*/
  					printf("Threshold temperature specified : >%s<, len=%u -> 0x%04lx\n", (STRPTR)result[OPT_THYST], s, thyst_fp);
  				}

        	//for (argNo=size-1; argNo > 0; --argNo) {
        	//	buf[argNo] = (UBYTE)(0xFF & thyst_fp);
        	//	thyst_fp >>= 8;
        	//}
          buf[2] = (UBYTE)(0xFF & thyst_fp);
          thyst_fp >>= 8;
          buf[1] = (UBYTE)(0xFF & thyst_fp);
          buf[0] = 0x02; /* Thyst register */

      		SendI2C(chip_addr << 1, size, buf);
  			}
  			FreeArgs(myrda);
  		}
  		FreeDosObject(DOS_RDARGS, myrda);
  	} else {
  		PutStr("Usage: " TEMPLATE "\n");
  	}

    CloseLibrary((struct Library *)I2CBase);
  }
  else
    Printf("Failed to open i2c.library\n");
  return 0;
}
