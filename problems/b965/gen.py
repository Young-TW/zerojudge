#!/usr/bin/env python3
"""b965 測資產生器：單筆測資（APCS 原題格式），R C M 各 1~10。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
R, C, M = rng.randint(1, 10), rng.randint(1, 10), rng.randint(1, 10)
print(R, C, M)
for _ in range(R):
    print(' '.join(str(rng.randint(0, 9)) for _ in range(C)))
print(' '.join(str(rng.randint(0, 1)) for _ in range(M)))
