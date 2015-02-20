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
# make
#   run all tests
#
# make { all | byte | opt | none }
#   run all tests, only byte-code tests, only native-code tests, or no tests
#
# make [ all | byte | opt | none ] file=<f>
#   run tests in all the directories listed in file <f>
#
# make [ all | byte | opt | none ] dir=<d>
#   run tests in directory <d>
#
# make [ all | byte | opt | none ] dir=<file>.t
#   run the tests described by <file>.t
#
# make [ all | byte | opt | none ] dir="<d1> ... <dn> <f1>.t ... <fn>.t"
#   run tests in the directories <d1> to <dn> and in files <f1>.t ... <fn>.t

ifeq "$(file)" ""
  dir=tests
else
  dir=$(shell cat $(file))
endif

#########################################################################
# set up configuration variables

TOPDIR=$(shell cd .. && pwd)
WINTOPDIR=$(shell cygpath -m $(TOPDIR))

# TOPDIR is the root directory of the OCaml sources, in Unix syntax.
# WINTOPDIR is the same directory, in Windows syntax.

OTOPDIR=$(TOPDIR)
CTOPDIR=$(TOPDIR)
CYGPATH=echo
DIFF=diff
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
# DIFF is a "diff" command that ignores trailing CRs under Windows.
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
unexport WINTOPDIR
export
export MAKE

.PHONY: all
all:
	rm -f _log _full-log
	$(MAKE) clean >>_full-log 2>&1
	$(MAKE) -C lib byte opt >>_full-log 2>&1
	./scripts/do_tests $(dir)

byte:
	rm -f _log _full-log
	$(MAKE) clean >>_full-log 2>&1
	$(MAKE) -C lib byte >>_full-log 2>&1
	./scripts/do_tests -no-opt $(dir)

opt:
	rm -f _log _full-log
	$(MAKE) clean >>_full-log 2>&1
	$(MAKE) -C lib opt >>_full-log 2>&1
	./scripts/do_tests -no-byte $(dir)

none:
	rm -f _log _full-log
	$(MAKE) clean >>_full-log 2>&1
	./scripts/do_tests -no-byte -no-opt $(dir)

.PHONY: clean
clean:
	scripts/do_clean tests

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
	echo '"make promote" is deprecated, you must promote by hand'
	exit 2

.PHONY: lib
lib:
	:

.PHONY: report
report:
	awk -f scripts/summary _log expected=
