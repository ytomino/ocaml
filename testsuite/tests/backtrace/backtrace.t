Tcompflags=-g
Texec_env=OCAMLRUNPARAM=b=1

Ttests=Tbyte_compile
Tmultiple Tbyte_run a b c d none
Ttests="$Ttests Topt_compile"
Tmultiple Topt_run a b c d none
