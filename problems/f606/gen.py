#!/usr/bin/env python3
"""f606 測資產生器：n m k、Q 矩陣（跨越 1000 流量門檻）、k 個方案。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
n, m, k = rng.randint(1, 6), rng.randint(1, 6), rng.randint(1, 6)
print(n, m, k)
for _ in range(n):
    print(' '.join(str(rng.randint(0, 3000)) for _ in range(m)))
for _ in range(k):
    print(' '.join(str(rng.randrange(m)) for _ in range(n)))
