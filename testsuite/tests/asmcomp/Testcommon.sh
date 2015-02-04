Topt_compile () {
    Pexport_variables
    $MAKE all $Pbase.o
    $NATIVECC -o $Pbase.exe $cflags $Pbase.o $ARCH.o
}
Ttests=Topt_compile_run
