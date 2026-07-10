#!/usr/bin/env python3
"""c292 測資產生器：N（奇數 3~9）、起始方向 0~3、N×N 個 0~9。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
N = rng.choice([3, 5, 7, 9])
print(N)
print(rng.randint(0, 3))
for _ in range(N):
    print(' '.join(str(rng.randint(0, 9)) for _ in range(N)))
