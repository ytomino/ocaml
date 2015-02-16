#########################################################################
#                                                                       #
#                                 OCaml                                 #
#                                                                       #
#                 Xavier Clerc, SED, INRIA Rocquencourt                 #
#                                                                       #
#   Copyright 2010 Institut National de Recherche en Informatique et    #
#   en Automatique.  All rights reserved.  This file is distributed     #
#   under the terms of the Q Public License version 1.0.                #
#                                                                       #
#########################################################################

BASEDIR=../..

CC=$(NATIVECC)
CFLAGS=$(NATIVECCCOMPOPTS) -g

INCLUDES=\
  -I $(OTOPDIR)/utils \
  -I $(OTOPDIR)/typing \
  -I $(OTOPDIR)/bytecomp \
  -I $(OTOPDIR)/asmcomp

OTHEROBJS=\
  $(OTOPDIR)/compilerlibs/ocamlcommon.cma \
  $(OTOPDIR)/compilerlibs/ocamloptcomp.cma

OBJS=parsecmmaux.cmo parsecmm.cmo lexcmm.cmo

ADD_COMPFLAGS=$(INCLUDES) -g

.PHONY: all
all: arch codegen

codegen: parsecmm.ml lexcmm.ml $(OBJS:.cmo=.cmi) $(OBJS) main.cmo
	$(OCAMLC) $(LINKFLAGS) -o codegen $(OTHEROBJS) $(OBJS) main.cmo

# parsecmm.mli parsecmm.ml: parsecmm.mly
# 	$(Pyacc) -q parsecmm.mly

# lexcmm.ml: lexcmm.mll
# 	$(Plex) -q lexcmm.mll

include $(TOPDIR)/testsuite/makefiles/Makefile.common

power.o: power-$(SYSTEM).o
	cp power-$(SYSTEM).o power.o

arch: $(ARCH).o

clean:
	rm -f ./codegen parsecmm.ml parsecmm.mli lexcmm.ml
