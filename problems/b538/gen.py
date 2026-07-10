#!/usr/bin/env python3
"""b538 測資產生器：每列 a b c d op，b,d 不為 0，除法時 c 不為 0。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
nz = [x for x in range(-20, 21) if x != 0]
for _ in range(rng.randint(1, 30)):
    op = rng.choice('+-*/')
    a = rng.randint(-99, 99)
    b = rng.choice(nz)
    c = rng.choice(nz) if op == '/' else rng.randint(-99, 99)
    d = rng.choice(nz)
    print(a, b, c, d, op)
