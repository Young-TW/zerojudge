#!/usr/bin/env python3
"""b884 測資產生器：n 與 n 行 x y（非負整數，涵蓋 yee 各區間邊界）。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
n = rng.randint(1, 20)
print(n)
for _ in range(n):
    print(rng.randint(0, 60), rng.randint(0, 60))
