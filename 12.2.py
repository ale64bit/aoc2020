import sys
from functools import reduce
from math import *
from cmath import *

ops = {
  'N': lambda p, wp, d : (p, wp + d*complex( 0.0,  1.0)),
  'S': lambda p, wp, d : (p, wp + d*complex( 0.0, -1.0)),
  'E': lambda p, wp, d : (p, wp + d*complex( 1.0,  0.0)),
  'W': lambda p, wp, d : (p, wp + d*complex(-1.0,  0.0)),
  'F': lambda p, wp, d : (p + d*(wp-p), p + d*(wp-p) + (wp-p)),
  'L': lambda p, wp, a : (p, (wp-p)*rect(1.0,  pi*a/180) + p),
  'R': lambda p, wp, a : (p, (wp-p)*rect(1.0, -pi*a/180) + p),
}

def f(st, line):
  op, val = line[0], int(line[1:])
  return ops[op](st[0], st[1], val)

p = reduce(f, sys.stdin, (complex(0.0, 0.0), complex(10.0, 1.0)))[0]
print(abs(p.real) + abs(p.imag))




