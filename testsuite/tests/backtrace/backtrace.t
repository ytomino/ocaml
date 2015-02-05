Tcompflags=-g
Texec_env=OCAMLRUNPARAM="${OCAMLRUNPARAM},b=1"

# Watch out, the order here is relevant:
Ttests=Tbyte_compile              # First compile with byte-code
Tmultiple Tbyte_run a b c d none  # Then run byte-code tests
Ttests="$Ttests Topt_compile"     # Then compile with native code
Tmultiple Topt_run a b c d none   # Then run native tests

Targs_a=a

Targs_b=b
Texit_b=2

Targs_c=c
Texit_c=2

Targs_d=d
Texit_d=2

Targs_none=
Texit_none=2
