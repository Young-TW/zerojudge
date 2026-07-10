import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep N small so an O(N^2)-per-query brute finishes well under 1s.
    N = rng.randint(1, 60)

    # A few queries per case, including boundary-ish ones.
    Q = rng.randint(1, 30)

    # Value pool: small magnitudes exercise ties heavily (the crux of this
    # problem); also occasionally push to large magnitudes / boundaries.
    out_lines = [f"{N} {Q}"]

    vals = []
    for _ in range(N):
        r = rng.random()
        if r < 0.45:
            lo, hi = -3, 3          # tiny magnitudes => many ties
        elif r < 0.65:
            lo, hi = 0, 0           # all-zero runs (extreme tie situations)
        elif r < 0.80:
            lo, hi = -10, 10
        elif r < 0.92:
            lo, hi = -50, 50
        else:
            # near boundaries of allowed absolute value
            if rng.random() < 0.5:
                lo, hi = 10 ** 9 - 5, 10 ** 9 - 1
            else:
                lo, hi = -(10 ** 9 - 1), -(10 ** 9 - 5)
        vals.append(rng.randint(lo, hi))
    out_lines.append(" ".join(str(v) for v in vals))

    # Make sure we cover boundary queries: full range, single-element, etc.
    queries = []
    for _ in range(Q):
        r = rng.random()
        if r < 0.15:
            L = R = rng.randint(1, N)              # single element
        elif r < 0.30:
            L, R = 1, N                            # whole array
        elif r < 0.45:
            L = 1
            R = rng.randint(1, N)
        elif r < 0.60:
            R = N
            L = rng.randint(1, N)
        else:
            L = rng.randint(1, N)
            R = rng.randint(L, N)
        queries.append((L, R))

    for (L, R) in queries:
        out_lines.append(f"{L} {R}")

    sys.stdout.write("\n".join(out_lines) + "\n")


main()
