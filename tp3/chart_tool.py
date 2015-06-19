#!/usr/bin/env python

import sys

import math
import matplotlib.pyplot as plt
import numpy as np

matrix  = []
for line in sys.stdin:
	matrix.append(line.split())

matrix = np.array(matrix)

# plt.ylabel("t/|V|^2")
plt.ylabel("Diferencia de cardinalidad goloso/exacto (%)")
plt.xlabel("Probabilidad de que dos ejes esten conectados")
plt.plot(matrix[:,0], matrix[:,1], 'ro-', label= "Regular")
# plt.axes.set_ytickslabel([])
# plt.plot(matrix[:,0], matrix[:,2], 'bo-', label= "Poda mejor solucion ya encontrada")
# plt.plot(matrix[:,0], matrix[:,3], 'go-', label= "Poda S no independiente")
# plt.plot(matrix[:,0], matrix[:,4], 'ko-', label= "Ambas podas")
#plt.legend(loc = 'middle right')
#plt.axis([0, 124750, 0, 0.1])
plt.show()