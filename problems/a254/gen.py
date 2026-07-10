#!/usr/bin/env python3
# Test case generator for ZeroJudge a254 (primitive Pythagorean triangles).
# Usage: python3 a254_gen.py <seed>
# Prints one valid random input to stdout, reproducible from the seed.
#
# Problem: given N sticks (positive ints in [1, 999999]), each used at most
# once, form as many primitive Pythagorean triangles as possible. A triangle
# uses two sticks as the two shorter legs a, b with a^2+b^2=c^2 (c integer)
# and gcd(a,b)==1. Maximize the count of disjoint such pairs.
#
# Scale kept small (N <= 16, few cases) so the exponential backtracking brute
# force finishes well under 1 second, while covering boundaries: N==1, large
# values, duplicates, and mixes of Pythagorean-generating pairs with noise.

import sys
import random


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def is_primitive_pair(a, b):
    if a <= 0 or b <= 0:
        return False
    if gcd(a, b) != 1:
        return False
    c2 = a * a + b * b
    c = int(c2 ** 0.5)
    # correct float drift
    while c > 0 and c * c > c2:
        c -= 1
    while (c + 1) * (c + 1) <= c2:
        c += 1
    return c * c == c2


def primitive_pairs(limit=2000):
    # generate (a, b) with a < b, a^2+b^2 square, gcd(a,b)==1, both <= limit.
    # Use Euclid's formula: a = m^2 - n^2, b = 2mn (m > n > 0, coprime, opp parity).
    res = []
    m = 2
    while True:
        if 2 * m > limit and (m * m - 1) > limit:
            break
        for n in range(1, m):
            if (m - n) % 2 == 0:
                continue
            if gcd(m, n) != 1:
                continue
            a = m * m - n * n
            b = 2 * m * n
            if a <= 0 or b <= 0:
                continue
            if a > limit or b > limit:
                continue
            lo, hi = (a, b) if a < b else (b, a)
            res.append((lo, hi))
        m += 1
        if m > limit:
            break
    return res


PAIRS = primitive_pairs(2000)


def main():
    rng = random.Random(int(sys.argv[1]))

    HI = 999999
    n_cases = rng.randint(1, 4)
    lines = [str(n_cases)]

    for _ in range(n_cases):
        scenario = rng.randint(0, 8)

        if scenario == 0:
            # N == 1: trivially zero triangles
            N = 1
            sticks = [rng.randint(1, HI)]
        elif scenario == 1:
            # boundary values: 1 and 999999, small N
            N = rng.randint(1, 6)
            sticks = [rng.choice([1, HI, rng.randint(1, HI)]) for _ in range(N)]
        elif scenario == 2:
            # all from genuine primitive Pythagorean pairs -> maximize matches
            count = rng.randint(2, 6)
            sticks = []
            for _ in range(count):
                a, b = rng.choice(PAIRS)
                sticks.append(a)
                sticks.append(b)
            rng.shuffle(sticks)
            N = len(sticks)
        elif scenario == 3:
            # pairs plus random noise sticks (non-Pythagorean) -> partial match
            count = rng.randint(1, 4)
            sticks = []
            for _ in range(count):
                a, b = rng.choice(PAIRS)
                sticks.append(a)
                sticks.append(b)
            extra = rng.randint(0, 4)
            for _ in range(extra):
                sticks.append(rng.randint(1, HI))
            rng.shuffle(sticks)
            N = len(sticks)
        elif scenario == 4:
            # duplicates of the same pair: e.g. several (3,4) -> count limited by pairs
            a, b = rng.choice(PAIRS)
            N = rng.randint(2, 10)
            sticks = [rng.choice([a, b]) for _ in range(N)]
        elif scenario == 5:
            # competing sticks: shared leg so greedy can fail
            # build a small "chain": stick values that each pair with multiple
            base_pairs = rng.sample(PAIRS, min(4, len(PAIRS)))
            sticks = []
            for (a, b) in base_pairs:
                sticks.append(a)
                sticks.append(b)
            # duplicate one shared leg to create contention
            if base_pairs:
                shared = base_pairs[0][0]
                sticks.append(shared)
            rng.shuffle(sticks)
            N = len(sticks)
        elif scenario == 6:
            # non-primitive multiples: (6,8) etc -> gcd != 1, should NOT count
            a, b = rng.choice(PAIRS)
            k = rng.randint(2, 5)
            N = rng.randint(2, 8)
            sticks = [rng.choice([a * k, b * k]) for _ in range(N)]
        elif scenario == 7:
            # small random values, low range (classic small triples like 3,4,5; 5,12,13)
            N = rng.randint(1, 12)
            sticks = [rng.randint(1, 60) for _ in range(N)]
        else:
            # general random up to HI, small N
            N = rng.randint(1, 14)
            sticks = [rng.randint(1, HI) for _ in range(N)]

        lines.append(str(N))
        lines.append(" ".join(str(x) for x in sticks))

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
