#########################################################################
#                                                                       #
#                                 OCaml                                 #
#                                                                       #
#                Damien Doligez, Jane Street Capital                    #
#                                                                       #
#   Copyright 2014 Institut National de Recherche en Informatique et    #
#   en Automatique.  All rights reserved.  This file is distributed     #
#   under the terms of the Q Public License version 1.0.                #
#                                                                       #
#########################################################################

# usage:
#
# make file=<f>
#   run tests in all the directories listed in file <f>
#
# make dir=<d>
#   run tests in directory <d>
#
# make dir=<file>.t
#   run the tests described by <file>.t
#
# make dir="<d1> ... <dn> <f1>.t ... <fn>.t"
#   run tests in the directories <d1> to <dn> and in files <f1>.t ... <fn>.t

ifeq "${file}" ""
  dir=tests
else
  dir=$(shell cat ${file})
endif

#########################################################################
# set up configuration variables

TOPDIR=$(shell pwd)/..
WINTOPDIR=$(shell cygpath -m $(TOPDIR))

# TOPDIR is the root directory of the OCaml sources, in Unix syntax.
# WINTOPDIR is the same directory, in Windows syntax.

OTOPDIR=$(TOPDIR)
CTOPDIR=$(TOPDIR)
CYGPATH=echo
DIFF=diff -q
CANKILL=true
SORT=sort
SET_LD_PATH=CAML_LD_LIBRARY_PATH="$(LD_PATH)"

# The variables above may be overridden by .../config/Makefile
# OTOPDIR is either TOPDIR or WINTOPDIR, whichever is appropriate for
#   arguments given to the OCaml compiler.
# CTOPDIR is either TOPDIR or WINTOPDIR, whichever is appropriate for
#   arguments given to the C and Fortran compilers.
# CYGPATH is the command that translates unix-style file names into
#   whichever syntax is appropriate for arguments of OCaml programs.
# DIFF is a "diff -q" command that ignores trailing CRs under Windows.
# CANKILL is true if a script launched by Make can kill an OCaml process,
#   and false for the mingw and MSVC ports.
# SORT is the Unix "sort" command. Usually a simple command, but may be an
#   absolute name if the Windows "sort" command is in the PATH.
# SET_LD_PATH is a command prefix that sets the path for dynamic libraries
#   (CAML_LD_LIBRARY_PATH for Unix, PATH for Windows) using the LD_PATH make
#   variable. Note that for Windows we add Unix-syntax directory names in
#   PATH, and Cygwin will translate it to Windows syntax.

include $(TOPDIR)/config/Makefile

# Transmit Makefile configuration variables to the test scripts
ENV = TOPDIR='$(TOPDIR)' \
      UNIXLIB='$(UNIXLIB)' \
      EXE='$(EXE)' \
      SUPPORTS_SHARED_LIBRARIES='$(SUPPORTS_SHARED_LIBRARIES)' \
      ARCH='$(ARCH)' \
      SYSTEM='$(SYSTEM)' \
      NATIVECC='$(NATIVECC)' \
      NATIVECCCOMPOPTS='$(NATIVECCCOMPOPTS)' \
      ASM='$(ASM)' \
      ASPP='$(ASPP)' \
      OTHERLIBRARIES='$(OTHERLIBRARIES)' \
      O='$(O)' \
      A='$(A)' \
      SO='$(SO)' \
      BYTECC='$(BYTECC)' \
      OTOPDIR='$(OTOPDIR)' \
      CYGPATH='$(CYGPATH)' \
      DIFF='$(DIFF)' \
      CANKILL='$(CANKILL)' \
      SORT='$(SORT)' \
      SET_LD_PATH='$(SET_LD_PATH)' \
      MAKE='$(MAKE)'

.PHONY: all
all:
	$(ENV) ./scripts/do_tests $(dir)

.PHONY: clean
clean:
	find tests -name '*.t' | while read f; do \
	  b=$${f%.t}; \
	  rm -f $$b.exe $$b.tmp_* $$b-*.tmp_*; \
	  ( cd `dirname $$b` && \
            ( rm -f *.cm[aiostx] *.cmx[as] *.cmti *.$(O) *.$(SO) *.$(A); \
              rm -rf *.dSYM ) ); \
        done
	find tests -name '*.clean' | while read f; do \
	  (cd `dirname $$f` && . ./`basename $$f`); \
	done
	rm -f _log _full-log

#####
# For compatibility with the old test makefile

.PHONY: list
list:
	$(MAKE) file=$(FILE)

.PHONY: one
one:
	$(MAKE) dir=$(DIR)

.PHONY: promote
promote:
	@echo '"make promote" is deprecated, you must promote by hand'

.PHONY: lib
lib:
	:

.PHONY: report
report:
	awk -f scripts/summary _log expected=
