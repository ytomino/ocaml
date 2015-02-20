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

kinds=opt

cbase=$base
opt_comp () {
    log $MAKE all $cbase.o
    log $NATIVECC $NATIVECCCOMPOPTS -g -o $opt_exec $cflags $cbase.o $ARCH.o
    launch :
}

clean () {
    clean_default
    "$MAKE" clean
}
