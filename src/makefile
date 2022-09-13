CFLAGS = -noixemul -I../include -I../include/C
LFLAGS = -noixemul -s
GCC = m68k-amigaos-gcc
delete=rm -rf

DBG = -ldebug -DDEBUG

EXECS = lm75 \
 lm75th \
 hwmon \
 i2cdetect \
 i2cget \
 i2cset

all: $(EXECS)
.PHONY: all

$(EXECS): %: %.c
	$(GCC) $(CFLAGS) -o $@ $^ $(DBG)

clean:
	${delete} ${EXECS}
