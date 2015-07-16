#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

import math
import matplotlib.pyplot as plt
import numpy as np

print("Ingrese los datos:")
matrix  = []
for line in sys.stdin:
	matrix.append(line.split())

matrix = np.array(matrix)


title = raw_input("Ingrese el nombre del grafico: ").decode('utf-8')
plt.title(title)
xl = raw_input("Ingrese la etiqueta del eje x: ").decode('utf-8')
plt.xlabel(xl)
yl = raw_input("Ingrese la etiqueta del eje y: ").decode('utf-8')
plt.ylabel(yl)
filename = raw_input("Ingrese el nombre de archivo:")

linestyles = ['-', '--', '-.', ':', 'None', ' ', '']
markerstyles = ["o", "s", "v", "^", "<", ">", "8", "p", "*", "h", "H", "+", "x"]
colors = ['k', 'r', 'g', 'b', 'c', 'm']

for i in range(1, matrix.shape[1]):
	formatt = colors[i%len(colors)] + markerstyles[i%len(markerstyles)] + linestyles[i%len(linestyles)]
	name = raw_input("Ingrese la leyenda de la columna " + str(i+1) + ": ").decode('utf-8')
	plt.plot(matrix[:,0], matrix[:,i], formatt, label= name)

plt.legend(loc='best')
#plt.axis([0, 124750, 0, 0.1])
plt.savefig(filename)
plt.show()