Tcompflags=-g
Texec_env=OCAMLRUNPARAM=b=1

Ttests=Tbyte_compile
Tmultiple Tbyte_run a b c d none

Ttests="$Ttests Topt_compile"
Tmultiple Topt_run a b c d none

Targs_a=a

Targs_b=b
Texit_b=2

Targs_c=c
Texit_c=2

Targs_d=d
Texit_d=2

Targs_none=
Texit_none=2
