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

sources="unix.cma bigarray.cma $base.ml"
compflags="-I $OTOPDIR/otherlibs/$UNIXLIB -I $OTOPDIR/otherlibs/bigarray"
LD_PATH=$TOPDIR/otherlibs/$UNIXLIB:$TOPDIR/otherlibs/bigarray
