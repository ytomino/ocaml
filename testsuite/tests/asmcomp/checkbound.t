cflags="-DCHECKBOUND main.c"
. _common.sh
Ttests="Topt_compile Topt_run_1 Topt_run_2"

Topt_run_1 () {
    Pbase="$Pbase-1"
    Topt_run
}

Topt_run_2 () {
    Pbase="$Pbase-2"
    Topt_run
}
