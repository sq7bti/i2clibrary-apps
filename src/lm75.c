/* Programmheader

	Name:		lm75.c
	Main:		I2C
	Versionstring:	$VER: Test.c 1.1 (21.09.2002)
	Author:		BTI
	Distribution:	Freeware
	Description:	the I2C library example usage program
  Usage: specify offset address of lm75 chip

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

UBYTE addr = 0x20, s;
UWORD number = 0;
UBYTE buf[2] = { 0x00, 0x00 };
ULONG error_code;
unsigned short temperat;
UBYTE i2c_sensor_addr, s;

/* My custom RDArgs */
struct RDArgs *myrda;

#define TEMPLATE "A=Address/A/N/M"
LONG *result;
UBYTE **adarray;

int main(int argc, char **argv)
{
  I2CBase = (struct I2CBase *) OpenLibrary("i2c.library", 39);

  if(I2CBase) {
    if (myrda = (struct RDArgs *)AllocDosObject(DOS_RDARGS, NULL)) {
  		/* parse my command line */
  		if (ReadArgs(TEMPLATE, result, myrda)) {
  			adarray = (UBYTE**)result[0];
  			for(UWORD n=0; adarray[n]; ++n) {
  				i2c_sensor_addr = (0x48 + *((LONG *)adarray[n]));
			    buf[0] = 0x00; /* configuration register */
  				buf[1] = 0x00; /* high resolution */

  				if(ReceiveI2C(i2c_sensor_addr << 1, 2, buf) == 2) {
            s = ' ';
  					if (buf[0] & 0x80) {
  						buf[0] ^= 0xFF;
  						buf[1] ^= 0xFF;
  						s = '-';
  					}
			      temperat = buf[1];
  					temperat *= 100;
  					temperat >>= 8;
  					printf("%s0x%02x: %c%d.%02d%cC", n==0?"":", ", i2c_sensor_addr, s, buf[0], temperat, 0xB0);
  				}
  			}
  			FreeArgs(myrda);
  			printf("\n");
  		}
  		FreeDosObject(DOS_RDARGS, myrda);
  	}

    CloseLibrary((struct Library *)I2CBase);
//    CloseLibrary(I2CBase);
  }
  else
    printf("Failed to open i2c.library\n");
  return 0;
}
