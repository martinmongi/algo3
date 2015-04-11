#!/bin/bash
# Uso para probar correctitud
#     TESTDIR=dir_de_los_in ./test.sh ../binario 
#
# Uso para medir tiempos
#     TESTDIR=dir_de_los_in ./test.sh ../binario tiempos
VALGRIND=valgrind
TESTDIR=${TESTDIR:-./catedra}
BINFILE=$1
EXT=".out"
MEM=${MEM:-NO}

OK=1
OKVALGRIND=1
for i in $( ls $TESTDIR/*.in); do
	echo testeando $i
	#ALUMNO=$i$EXT
	ALUMNO=${i/in/alumno.out}
	rm -f $ALUMNO
	CATEDRA=${i/in/out}
	# rm -f $CATEDRA
        if [ "x$2" != "xtiempos" ]; then
            if [ "$MEM" == "NO" ]; then
                #$BINFILE < $i > $ALUMNO
                $BINFILE < $i | head -n 1 | cut -d" " -f1 > $ALUMNO
            else
	        $VALGRIND --show-reachable=yes --leak-check=yes --error-exitcode=1 -q $BINFILE < $i > $ALUMNO
            fi
	    if [ $? != "0" ]; then
    		OKVALGRIND=0
 	    fi
	    diff -q --strip-trailing-cr $CATEDRA $ALUMNO
	    if [ $? != "0" ]; then
		OK=0
            fi
        else
            $BINFILE < $i >> tiempos.dat
        fi
done
if [ $OK != "0" ] && [ $OKVALGRIND != "0" ]; then
	echo "Tests finalizados correctamente"
else 
    echo "Algunos tests estan mal"
fi

