import sys
from functools import reduce
from math import *
from cmath import *

ops = {
  'N': lambda p, phi, d : (p + d*complex( 0.0,  1.0), phi),
  'S': lambda p, phi, d : (p + d*complex( 0.0, -1.0), phi),
  'E': lambda p, phi, d : (p + d*complex( 1.0,  0.0), phi),
  'W': lambda p, phi, d : (p + d*complex(-1.0,  0.0), phi),
  'F': lambda p, phi, d : (p + d*rect(1.0, phi), phi),
  'L': lambda p, phi, a : (p, phi + pi*a/180),
  'R': lambda p, phi, a : (p, phi - pi*a/180),
}

def f(st, line):
  op, val = line[0], int(line[1:])
  return ops[op](st[0], st[1], val)

p = reduce(f, sys.stdin, (complex(0.0, 0.0), 0.0))[0]
print(abs(p.real) + abs(p.imag))




