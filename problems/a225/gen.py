#!/usr/bin/env python3
"""a225 測資產生器：多組到 EOF，每組 n 與 n 個整數。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
for _ in range(rng.randint(1, 5)):
    n = rng.randint(1, 30)
    print(n)
    print(' '.join(str(rng.randint(0, 1000)) for _ in range(n)))
