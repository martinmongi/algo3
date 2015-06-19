#!/bin/bash
	for p in `seq .00 0.05 1`;
	do
		for v in `seq 15 1 15`;
		do
			rm results_exact.out
			rm results_greedy.out
			
		    for i in `seq 1 20`;
	        do
	        		python3 generator.py $v $p
	                ./cidm EXACT < test.in >> results_exact.out 2>> /dev/null
	                ./cidm LOCAL_SEARCH_GREEDY_2 < test.in >> results_greedy.out 2>> /dev/null
	        done
	        printf $v
			printf ', '
			printf $p
			printf ', '
	        cat results_exact.out | python3 vertex_average.py
			printf ', '
	        cat results_greedy.out | python3 vertex_average.py
	        printf '\n'
	    done
	done