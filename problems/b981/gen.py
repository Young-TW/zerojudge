#!/usr/bin/env python3
"""b981 測資產生器：多行到 EOF，每行一種時間格式。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
for _ in range(rng.randint(1, 30)):
    x, y, z = rng.randrange(24), rng.randrange(60), rng.randrange(60)
    a, b = rng.randrange(10), rng.randrange(1000)
    print(rng.choice([
        f"{x}hour", f"{x}h{y}m", f"{x}h{y}m{z}s",
        f"{y}min", f"{y}m{z}s", f"{z}s", f"{z}.{a}s", f"{b}ms",
    ]))
