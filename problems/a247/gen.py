#!/usr/bin/env python3
# Test case generator for ZeroJudge a247.
# Usage: python3 a247_gen.py <seed>
# Prints one valid random input (multiple lines) to stdout, reproducible
# from the seed. Scale is kept small so the brute force finishes well under
# 1 second, but boundary and sample values are covered.

import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    n_lines = rng.randint(1, 5)
    out = []
    for _ in range(n_lines):
        scenario = rng.randint(0, 6)
        if scenario == 0:
            N = 1                       # minimum: no triple possible
        elif scenario == 1:
            N = 10                      # sample value
        elif scenario == 2:
            N = 25                      # sample value
        elif scenario == 3:
            N = 100                     # sample value
        elif scenario == 4:
            N = 500                     # sample value
        elif scenario == 5:
            N = rng.randint(1, 30)      # tiny random
        else:
            N = rng.randint(1, 2500)    # moderate random, brute stays fast
        out.append(str(N))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
