#!/usr/bin/env python3
"""b759 測資產生器：一行純英文字母字串。"""
import random, string, sys

rng = random.Random(int(sys.argv[1]))
print(''.join(rng.choice(string.ascii_letters) for _ in range(rng.randint(1, 60))))
