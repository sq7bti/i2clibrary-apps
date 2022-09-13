/* Programmheader

	Name:		hwmon.c
	Main:		I2C
	Versionstring:	$VER: Test.c 1.1 (13.09.2022)
	Author:		BTI
	Distribution:	Freeware
	Description:	the I2C library example usage program

 1.0   13.09.22 : initial code
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
UBYTE buf[2] = { 0x00, 0x00 };
ULONG error_code;
unsigned short temperat;
UBYTE i2c_sensor_addr, s;

void fpmath() {
  s = ' ';
  if (buf[0] & 0x80) {
    buf[0] ^= 0xFF;
    buf[1] ^= 0xFF;
    s = '-';
  }
  temperat = buf[1];
  temperat *= 100;
  temperat >>= 8;
}
int main(int argc, char **argv)
{
  I2CBase = (struct I2CBase *) OpenLibrary("i2c.library", 39);

  if(I2CBase) {

    if(ReceiveI2C(0x48 << 1, 2, buf) == 2) {
      fpmath();
      printf("MCU: %c%d.%02d%cC; ", s, buf[0], temperat, 0xb0);
  	}
    if(ReceiveI2C(0x49 << 1, 2, buf) == 2) {
      fpmath();
      printf("CPU: %c%d.%02d%cC; ", s, buf[0], temperat, 0xb0);
  	}
    if(ReceiveI2C(0x4A << 1, 2, buf) == 2) {
      printf("PWM %d%%, ", (100*(256*buf[0] + buf[1]))/512);
  	}
    if(ReceiveI2C(0x4B << 1, 2, buf) == 2) {
      printf("Tacho max %drpm, current %drpm", 30 * buf[0], 30 * buf[1]);
  	}
    printf("\n");

    CloseLibrary((struct Library *)I2CBase);
//    CloseLibrary(I2CBase);
  }
  else
    Printf("Failed to open i2c.library\n");
  return 0;
}
