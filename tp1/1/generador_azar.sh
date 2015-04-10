#!/bin/bash
# Uso: ./test.sh binario testdir repeticion "parametros para seq"
# ejemplo: complejidad/generador_azar.sh ./complejidad/generador ./tiempos 4 "100 100 10000"
VALGRIND=valgrind
TESTDIR=$2
BINFILE=$1
REPETICION=$3
EXT=".out"

OK=1
OKVALGRIND=1
if [ "x$REPETICION" != "x" ]; then
    rm -f tiempos.dat
    rm -f $TESTDIR/*_tiempos.in

    for n in $(seq -f "%06g" $4); do
        $BINFILE $n > $TESTDIR/${n}_tiempos.in
    done
fi
for i in $( ls $TESTDIR/*.in); do
	echo testeando $i
	#ALUMNO=$i$EXT
	ALUMNO=${i/in/alumno.out}
	rm -f $ALUMNO
	CATEDRA=${i/in/out}
	# rm -f $CATEDRA
        if [ "x$REPETICION" == "x" ]; then
            $BINFILE < $i | cut -d" " -f1 > $ALUMNO
	    #$VALGRIND --show-reachable=yes --leak-check=yes --error-exitcode=1 -q $BINFILE -i $i -o $ALUMNO
	    #$VALGRIND --show-reachable=yes --leak-check=yes --error-exitcode=1 -q $BINFILE -i $i -o $CATEDRA
	    if [ $? != "0" ]; then
    		OKVALGRIND=0
 	    fi
	    diff -q --strip-trailing-cr $CATEDRA $ALUMNO
	    if [ $? != "0" ]; then
		OK=0
            fi
        else
            for rep in $(seq 1 $REPETICION); do
                ./complejidad/zombieTiempos < $i >> tiempos.dat
            done
        fi
        sleep 0.3
done
if [ $OK != "0" ] && [ $OKVALGRIND != "0" ]; then
	echo "Tests finalizados correctamente"
fi

