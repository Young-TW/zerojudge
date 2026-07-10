#!/usr/bin/env python3
"""c013 測資產生器：首行 n，空行，之後每組兩行 A、F，組間空行。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
n = rng.randint(1, 4)
cases = [f"{rng.randint(1, 9)}\n{rng.randint(1, 4)}" for _ in range(n)]
print(n)
print()
print('\n\n'.join(cases))
