#!/usr/bin/env python3
"""f580 測資產生器：n m 與 m 個操作（交換 / 向前轉 / 向右轉）。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
n, m = rng.randint(1, 6), rng.randint(1, 20)
print(n, m)
for _ in range(m):
    t = rng.randrange(3)
    if t == 0 and n >= 2:
        a, b = rng.sample(range(1, n + 1), 2)
        print(a, b)
    elif t == 1:
        print(rng.randint(1, n), -1)
    else:
        print(rng.randint(1, n), -2)
