#!/usr/bin/env python3
# Test case generator for ZeroJudge a245.
# Usage: python3 a245_gen.py <seed>
# Prints one valid random input to stdout, reproducible from the seed.
#
# Problem: for each test case, given N points with integer coords in
# [-10000, 10000], find an integer point P minimizing the sum of Manhattan
# distances to all given points. Output the min sum and the count of
# integer points achieving it (over ALL integer points, not just the box).
#
# Scale is kept small (few cases, small N, tight coordinate ranges) so the
# O(box_area * N) brute force finishes well under 1 second, but boundary
# conditions are exercised: N==1, N==2, even/odd N, degenerate collinear
# points, duplicate points, and the coordinate limits +/-10000.

import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    LO = -10000
    HI = 10000

    n_cases = rng.randint(1, 5)
    lines = [str(n_cases)]

    for _ in range(n_cases):
        scenario = rng.randint(0, 7)
        # keep N tiny so the brute scan stays fast
        N = rng.randint(1, 12)

        pts = []
        if scenario == 0:
            # general random small range
            for _ in range(N):
                pts.append((rng.randint(-20, 20), rng.randint(-20, 20)))
        elif scenario == 1:
            # single point: every integer P is optimal (sum 0 everywhere)
            N = 1
            pts.append((rng.randint(LO, HI), rng.randint(LO, HI)))
        elif scenario == 2:
            # two points: whole segment between them is optimal
            N = 2
            x0 = rng.randint(LO, HI)
            y0 = rng.randint(LO, HI)
            x1 = rng.randint(LO, HI)
            y1 = rng.randint(LO, HI)
            pts = [(x0, y0), (x1, y1)]
        elif scenario == 3:
            # all identical points -> single median, count 1
            N = rng.randint(1, 8)
            x0 = rng.randint(-50, 50)
            y0 = rng.randint(-50, 50)
            pts = [(x0, y0) for _ in range(N)]
        elif scenario == 4:
            # even N -> median is a rectangle, count > 1 generally
            N = rng.choice([2, 4, 6, 8])
            for _ in range(N):
                pts.append((rng.randint(-15, 15), rng.randint(-15, 15)))
        elif scenario == 5:
            # odd N -> median is a single point, count usually 1
            N = rng.choice([3, 5, 7, 9])
            for _ in range(N):
                pts.append((rng.randint(-15, 15), rng.randint(-15, 15)))
        elif scenario == 6:
            # degenerate collinear (horizontal) -> count spans x range
            N = rng.randint(2, 8)
            y0 = rng.randint(-30, 30)
            xs = sorted(rng.randint(-20, 20) for _ in range(N))
            pts = [(x, y0) for x in xs]
        else:
            # boundary coordinates near +/-10000 with small N
            N = rng.randint(1, 6)
            edge_x = rng.choice([LO, HI, 0])
            edge_y = rng.choice([LO, HI, 0])
            for _ in range(N):
                x = rng.choice([LO, HI, edge_x, rng.randint(LO, HI)])
                y = rng.choice([LO, HI, edge_y, rng.randint(LO, HI)])
                pts.append((x, y))

        lines.append(str(N))
        for (x, y) in pts:
            lines.append(f"{x} {y}")

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
