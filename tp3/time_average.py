s0 = []
s1 = []
s2 = []
c = 0

import sys

for line in sys.stdin:
    s0.append(float(line.split(';')[0]))
    ##print(s0, s1, c)
    s1.append(float(line.split(';')[1]))
    s2.append(float(line.split(';')[2]))
    c = c + 1


print(str(s0[int(c/2)]) + ", " + str(s1[int(c/2)]) + ", " + str(s2[int(c/2)]))
