#!/usr/bin/env python3
"""Test case generator for ZeroJudge a571 (海港碼頭).

Usage: python3 a571_gen.py <seed>
Prints one legal (possibly multi-case) random input to stdout.

Scale is kept small so the brute force (2^N subset enumeration) finishes
well under a second, but boundary conditions are covered:
  - N up to ~12 per case (brute = 2^12 = 4096 subsets, trivial)
  - multiple test cases in one invocation (problem is multi-testcase)
  - small time range to force overlaps, shared endpoints, crossings
  - occasionally N=1, duplicate intervals, adjacent/identical endpoints
"""
import sys
from random import Random


def gen_case(rng):
    # Mostly small N so brute stays instant; occasionally push to 12.
    r = rng.random()
    if r < 0.15:
        n = 1
    elif r < 0.6:
        n = rng.randint(2, 6)
    else:
        n = rng.randint(7, 12)
    # Keep time range tight to force interactions (crossings, shared endpoints).
    span = rng.choice([6, 8, 10, 14, 20])
    lo = rng.randint(1, 5)
    hi = lo + span
    ships = []
    for _ in range(n):
        s = rng.randint(lo, hi - 1)
        e = rng.randint(s + 1, hi)
        ships.append((s, e))
    return n, ships


def main():
    seed = int(sys.argv[1])
    rng = Random(seed)
    # Emit a few test cases back-to-back (problem reads until EOF).
    ncases = rng.randint(1, 4)
    out = []
    for _ in range(ncases):
        n, ships = gen_case(rng)
        out.append(str(n))
        for s, e in ships:
            out.append(f"{s} {e}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
