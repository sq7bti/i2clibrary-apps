/*========================================================================*\
 |  File: i2cdetect.c                                  Date: 13 Mar 2022  |
 *------------------------------------------------------------------------*
 |  Look who's listening on the I2C bus, using i2c.library                |
 |  Usage:                                                                |
 |    i2cdetect                                                           |
 |  Return values:                                                        |
 |   0 = OK                                                               |
 |   5 = no listeners detected                                            |
 |  10 = scan failed due to resource allocation problems                  |
 |  15 = errors occured which might indicate a hardware problem           |
 |  20 = library not found                                                |
 |                                                                        |
\*========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <proto/exec.h>
#include <proto/i2c.h>
#include <libraries/i2c.h>

char *version = "$VER: i2cdetect 1.0";

struct I2CBase *I2CBase = 0;

int report( ULONG code )
/* analyze an i2clib return code, returns TRUE if it indicates an error */
{
  STRPTR s;

  if( code & 0xFF )   /* indicates OK */
    return FALSE;
  else
    return TRUE;
}


int scan( int verbose )
/* Return value of scan() is the one that the program itself should return, */
/* as explained at the top of this file. */
{
  int rd=0, wr=0, i;
  char dummy;
  int count=0;
  UBYTE chip_addr;
  UBYTE hb, lb;

  printf("   ");
	for(lb=0; lb<0x10; ++lb)
		printf("%3x", lb);
	printf("\n");

  for(hb=0x00; hb<0x80; hb += 0x10) {
		printf("%02x:", hb);
  	for(lb=0x00; lb<0x10; ++lb) {
  		chip_addr = hb | lb;

      if((chip_addr > 0x07) && (chip_addr < 0x78)) {
        if (!report( ReceiveI2C(chip_addr << 1, 1, &dummy) ) || !report( SendI2C(chip_addr << 1, 0, &dummy) )) {
          count++;
          printf(" %02x", chip_addr);
  			} else
  				printf(" --");
      } else
        printf("   ");
    }
    printf("\n");
  }
}

int ctrl_c;

void intercept( int class )
{
  ctrl_c = 1;
}

void cleanup()
{
  if( I2CBase ) {
    CloseLibrary((struct Library *)I2CBase );
    I2CBase = NULL;
  }
}


int main( int argc, char *argv[] )
{
  ULONG busdelay;
  int i, verbose=FALSE, lockit=FALSE, watch=FALSE;
  int result = 0;

  atexit( cleanup );   /* make sure library will be closed upon Ctrl-C */
  I2CBase = (struct I2CBase *) OpenLibrary( "i2c.library", 40 );
  if( I2CBase == NULL )
  {
    printf( "Can't open i2c.library V40\n" );
    return 20;
  }

  if( ((struct Library *)I2CBase)->lib_Version < 40 )
  {
    printf( "need i2c.library v40+ for this option\n" );
    exit( 20 );
  }

  printf("WARNING! This program can confuse your I2C bus, cause data loss and worse!\nI will probe address range 0x08-0x77.\nYou have been warned!\n");

  result = scan( verbose );

  cleanup();

  return result;
}
