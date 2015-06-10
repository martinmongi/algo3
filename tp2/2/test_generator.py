import sys
import random

n = int(sys.argv[1])
m = int(sys.argv[2])
s = int(sys.argv[3])

f = open("test.in", 'w')

f.write(str(n) + " " + str(m) + " " + str(s) + "\n")

f.write(str(random.randint(1,n)) + " " + str(random.randint(1,m)) + " " + str(random.randint(1,n)) + " " + str(random.randint(1,m)) + "\n")

for i in range(n-1):

	for j in range(m-1):
		f.write(str(random.randint(0,2*s)) + " ")

	f.write("\n")

	for j in range(m):
		f.write(str(random.randint(0,2*s)) + " ")

	f.write("\n")

for j in range(m-1):
	f.write(str(random.randint(0,2*s)) + " ")

f.write("\n")