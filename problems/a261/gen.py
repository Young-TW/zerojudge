#!/usr/bin/env python3
# Test case generator for ZeroJudge a261 (Dropping water balloons).
# Usage: python3 a261_gen.py <seed>
# Prints one valid random input to stdout, reproducible from the seed.
#
# Problem: k balloons (1<=k<=100), n floors (64-bit). Find the minimum number
# of trials in the worst case to determine the lowest breaking floor. If more
# than 63, print "More than 63 trials needed.". Input ends with "0 0".
#
# Scale kept small (few cases, modest n) so any brute force finishes fast,
# while covering boundaries: k=1, k=100, n=1, n=2^63-1, and n exactly at the
# f(t,k) / f(t,k)±1 answer-transition points.

import sys
import random

ULL_MAX = (1 << 64) - 1
N_MAX = (1 << 63) - 1  # signed 64-bit max, matching the sample's largest n


def f(t, k):
    # max floors distinguishable with t trials and k balloons
    #   = sum_{i=1}^{min(k,t)} C(t,i), capped at ULL_MAX
    lim = min(k, t)
    s = 0
    c = 1  # C(t, 0)
    for i in range(1, lim + 1):
        c = c * (t - i + 1) // i  # now c == C(t, i)
        s += c
        if s > ULL_MAX:
            return ULL_MAX
    return s


def main():
    rng = random.Random(int(sys.argv[1]))

    n_cases = rng.randint(1, 6)
    lines = []
    for _ in range(n_cases):
        scenario = rng.randint(0, 9)

        if scenario == 0:
            # k = 1: must scan linearly -> answer = n, "More than 63" when n>63
            k = 1
            n = rng.choice([1, 2, 5, 63, 64, 100, rng.randint(1, 200)])
        elif scenario == 1:
            # k at upper boundary
            k = 100
            n = rng.choice([1, 2, rng.randint(1, 1000), N_MAX])
        elif scenario == 2:
            # n = 1: answer always 1
            k = rng.randint(1, 100)
            n = 1
        elif scenario == 3:
            # n exactly f(t,k): answer is exactly t
            t = rng.randint(1, 63)
            k = rng.randint(1, 100)
            n = f(t, k)
            if n <= 0 or n > N_MAX:
                n = rng.randint(1, 1000)
        elif scenario == 4:
            # n = f(t,k) + 1: answer becomes t+1 (t<63 keeps it in range)
            t = rng.randint(1, 62)
            k = rng.randint(1, 100)
            n = f(t, k) + 1
            if n > N_MAX:
                n = N_MAX
        elif scenario == 5:
            # n = f(t,k) - 1: answer stays t (just below the transition)
            t = rng.randint(2, 63)
            k = rng.randint(1, 100)
            n = f(t, k) - 1
            if n <= 0 or n > N_MAX:
                n = 1
        elif scenario == 6:
            # large n near the 64-bit ceiling
            k = rng.randint(40, 100)
            n = rng.choice([N_MAX, N_MAX - 1, N_MAX - rng.randint(0, 1000)])
        elif scenario == 7:
            # tiny k, moderate n -> frequently "More than 63 trials needed."
            k = rng.randint(1, 3)
            n = rng.randint(1, 1000000)
        elif scenario == 8:
            # random small
            k = rng.randint(1, 100)
            n = rng.randint(1, 100000)
        else:
            # general random across the full 64-bit range
            k = rng.randint(1, 100)
            n = rng.randint(1, N_MAX)

        lines.append(f"{k} {n}")

    lines.append("0 0")
    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
