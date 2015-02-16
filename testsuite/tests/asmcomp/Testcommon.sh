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

Topt_compile () {
    Pexport_variables
    $MAKE all $Pbase.o
    $NATIVECC -o $Pbase.exe $cflags $Pbase.o $ARCH.o
}
Ttests=Topt_compile_run
