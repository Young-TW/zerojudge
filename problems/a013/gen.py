#!/usr/bin/env python3
"""a013 測資產生器：每行兩個羅馬數字（值 1~3999），最後一行 #。"""
import random, sys

rng = random.Random(int(sys.argv[1]))

def roman(n):
    vals = [(1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'), (100, 'C'), (90, 'XC'),
            (50, 'L'), (40, 'XL'), (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'), (1, 'I')]
    s = ''
    for v, sym in vals:
        while n >= v:
            s += sym
            n -= v
    return s

for _ in range(rng.randint(1, 20)):
    print(roman(rng.randint(1, 3999)), roman(rng.randint(1, 3999)))
print('#')
