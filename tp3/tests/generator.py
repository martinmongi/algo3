import sys
import random

n = int(sys.argv[1])
p = float(sys.argv[2])
f = open("test.in", 'w')
f.write(str(n) + "\n")

for i in range(0,n):
	for j in range(i + 1, n):
		if random.random() <= p:
			f.write(str(i) + " " + str(j) + "\n")

f.close()
