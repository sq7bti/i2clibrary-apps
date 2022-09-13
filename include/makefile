DPATH   = ./
AUTHOR  = "Dirk Stoecker"
BASE    = i2c

SFDNAME = $(DPATH)SFD/$(BASE)_lib.sfd

default: all

PRAGMAPATH = $(DPATH)C/pragma/
PRAGMANAME = $(PRAGMAPATH)$(BASE)_lib.h
$(PRAGMANAME): $(SFDNAME)
	fd2pragma --special   6 --infile $(SFDNAME) --to $(PRAGMAPATH)

AMIGAEPATH = $(DPATH)AmigaE/
AMIGAENAME = $(AMIGAEPATH)$(BASE).m
$(AMIGAENAME): $(SFDNAME)
	fd2pragma --special  18 --infile $(SFDNAME) --to $(AMIGAEPATH)

GCCINLINEPATH = $(DPATH)C/inline/
GCCINLINENAME = $(GCCINLINEPATH)$(BASE).h
$(GCCINLINENAME): $(SFDNAME)
	fd2pragma --special  40 --infile $(SFDNAME) --to $(GCCINLINEPATH)

PROTOPATH = $(DPATH)C/proto/
PROTONAME = $(PROTOPATH)$(BASE).h
$(PROTONAME): $(SFDNAME)
	fd2pragma --special  38 --infile $(SFDNAME) --to $(PROTOPATH)

VBCCINLINEPATH = $(DPATH)C/inline/
VBCCINLINENAME = $(VBCCINLINEPATH)$(BASE)_protos.h
$(VBCCINLINENAME): $(SFDNAME)
	fd2pragma --special  70 --infile $(SFDNAME) --to $(VBCCINLINEPATH)

LVOPATH = $(DPATH)ASM/lvo/
LVONAME = $(LVOPATH)$(BASE)_lib.i
$(LVONAME): $(SFDNAME)
	fd2pragma --special  23 --infile $(SFDNAME) --to $(LVOPATH)

FDPATH = $(DPATH)FD/
FDNAME = $(FDPATH)$(BASE)_lib.fd
$(FDNAME): $(SFDNAME)
	fd2pragma --special 110 --infile $(SFDNAME) --to $(FDPATH) --clib $(DPATH)C/clib/$(BASE)_protos.h --comment

CLIBPATH = $(DPATH)C/clib/
CLIBNAME = $(CLIBPATH)$(BASE)_protos.h
$(CLIBNAME): $(SFDNAME)
	fd2pragma --special 111 --infile $(SFDNAME) --to $(CLIBPATH) --clib $(DPATH)C/clib/$(BASE)_protos.h --comment --copyright $(AUTHOR)

all: $(PRAGMANAME) $(GCCINLINENAME) $(PROTONAME) $(FDNAME) $(CLIBNAME)

