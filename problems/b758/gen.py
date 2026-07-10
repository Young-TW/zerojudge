#!/usr/bin/env python3
"""b758 測資產生器：一行 X Y（現在時間 X:Y）。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
print(rng.randint(0, 23), rng.randint(0, 59))
