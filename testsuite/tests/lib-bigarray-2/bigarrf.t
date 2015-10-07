#########################################################################
#                                                                       #
#                                 OCaml                                 #
#                                                                       #
#                 Damien Doligez, Jane Street Capital                   #
#                                                                       #
#   Copyright 2015 Institut National de Recherche en Informatique et    #
#   en Automatique.  All rights reserved.  This file is distributed     #
#   under the terms of the Q Public License version 1.0.                #
#                                                                       #
#########################################################################

sources='unix.cma bigarray.cma bigarrf.f bigarrfstub.c bigarrfml.ml'
cflags="-I $CTOPDIR/otherlibs/bigarray"
compflags="-I $OTOPDIR/otherlibs/bigarray -I $OTOPDIR/otherlibs/$UNIXLIB \
           $FORTRAN_LIBRARY"
