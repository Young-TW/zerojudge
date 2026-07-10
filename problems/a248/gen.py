#!/usr/bin/env python3
# Test case generator for ZeroJudge a248.
# Usage: python3 a248_gen.py <seed>
# Prints one valid random input to stdout, reproducible from the seed.
# Scale is kept small so the brute force finishes well under 1 second,
# but edge cases (divisible, a<b, a==b, b==1, N==1, near INT_MAX) are covered.

import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    MAXV = 2147483647  # problem upper bound for a and b

    n_lines = rng.randint(1, 4)
    out = []
    for _ in range(n_lines):
        scenario = rng.randint(0, 6)
        N = rng.randint(1, 100)  # small N keeps everything fast

        if scenario == 0:
            # general random
            a = rng.randint(1, MAXV)
            b = rng.randint(1, MAXV)
        elif scenario == 1:
            # a divisible by b (trailing zeros)
            b = rng.randint(1, MAXV)
            k = rng.randint(1, max(1, MAXV // b))
            a = b * k
        elif scenario == 2:
            # a < b (integer part is 0)
            b = rng.randint(2, MAXV)
            a = rng.randint(1, b - 1)
        elif scenario == 3:
            # a == b (result 1.000...)
            a = rng.randint(1, MAXV)
            b = a
        elif scenario == 4:
            # b == 1 (pure integer result)
            a = rng.randint(1, MAXV)
            b = 1
        elif scenario == 5:
            # minimum precision
            N = 1
            a = rng.randint(1, MAXV)
            b = rng.randint(1, MAXV)
        else:
            # near INT_MAX for both
            a = rng.randint(2147483000, MAXV)
            b = rng.randint(2147483000, MAXV)

        out.append(f"{a} {b} {N}")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
