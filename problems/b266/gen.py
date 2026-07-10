#!/usr/bin/env python3
"""b266 測資產生器：多筆測資直到 EOF（judge 實際格式，無範例顯示用的 // 註解行）。"""
import random, sys

rng = random.Random(int(sys.argv[1]))
lines = []
for _ in range(rng.choice([1, 1, 2, 3])):
    R, C, M = rng.randint(1, 10), rng.randint(1, 10), rng.randint(1, 10)
    lines.append(f"{R} {C} {M}")
    for _ in range(R):
        lines.append(" ".join(str(rng.randint(0, 9)) for _ in range(C)))
    lines.append(" ".join(str(rng.randint(0, 1)) for _ in range(M)))
print("\n".join(lines))
