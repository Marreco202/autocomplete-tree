#!/bin/bash
# Script para compilar e executar programa 
for f in *.c; do echo "Processing ${f%.*} file..";gcc  -c ${f%.*}.c -o ${f%.*}.o; done
VARIABLE=$(for f in *.o; do echo " $f"; done)
gcc -o prog_t2_tries.exe $VARIABLE
./prog_t2_tries.exe
