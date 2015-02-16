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

. ./Testcommon.sh
cbase=checkbound
cflags="-DCHECKBOUND main.c"
args="1200 1000"
exit=2
