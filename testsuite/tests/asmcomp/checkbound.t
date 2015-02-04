. Testcommon.sh

cflags="-DCHECKBOUND main.c"
Ttests=Topt_compile; Tmultiple Topt_run 1 2
Targs_1="500 1000"
Texit_1=0
Targs_2="1200 1000"
Texit_2=2
