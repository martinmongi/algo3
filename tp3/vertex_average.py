s0 = 0.0
s1 = []
s2 = []
c = 0

import sys

for line in sys.stdin:
    s0 = s0 + float(line.split(' ')[0])
    c = c + 1

print(s0/float(c), end="")