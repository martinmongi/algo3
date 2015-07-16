#!/bin/bash
	
	for p in `seq .25 0.05 .25`;
	do
		for v in `seq 1 1 100`;
		do
			
			rm times.out
		    for i in `seq 1 100`;
	        do
	        		./generator.py $v $p
	                ./cidm GREEDY < test.in > /dev/null 2>> times.out
	        done
	        cat times.out | python3 average.py
	    done
	done