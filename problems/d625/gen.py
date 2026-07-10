#!/usr/bin/env python3
"""d625 測資產生器：n 與 n 行棋盤（- 空格、* 地雷）。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
n = rng.randint(1, 15)
print(n)
for _ in range(n):
    print(''.join('*' if rng.random() < 0.2 else '-' for _ in range(n)))
