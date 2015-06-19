#!/bin/bash
	
	
	
	for p in `seq .0 0.05 1.0`;
	do
		for v in `seq 500 20 500`;
		do
			rm times.out
			python3 ./tests/generator.py $v $p
		    for i in `seq 1 20`;
	        do
	        		
	                ./cidm GREEDY < test.in > /dev/null 2>> times.out
	        done
	        cat times.out | python3 time_average.py
	    done
	done