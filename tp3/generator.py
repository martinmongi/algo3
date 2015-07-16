#!/usr/bin/env python

#Genera un grafo aleatorio con parametros n y p
#Uso: ./generator.py n p
#n = numero de vertices del grafo
#p = probabilidad de que dos ejes del grafo esten conectados

import sys
import random

n = int(sys.argv[1])
p = float(sys.argv[2])

l = []
for i in range(1,n+1):
	for j in range(i + 1, n + 1):
		if random.random() <= p:
			l.append(str(i) + " " + str(j) + "\n")

f = open("test.in", 'w')

f.write(str(n) + " " + str(len(l)) + "\n")
for i in l:
	f.write(i)

f.close()
