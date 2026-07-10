import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Small sizes so the O(n*k) brute finishes instantly, but cover boundaries.
    n = rng.randint(1, 30)

    # Window size: bias towards interesting boundary values.
    r = rng.random()
    if r < 0.15:
        k = 1                       # window of size 1 -> min == max == element
    elif r < 0.30:
        k = n                       # single window covering whole array
    elif r < 0.45:
        k = rng.randint(1, n)       # generic
    else:
        k = rng.randint(1, max(1, n // 2))  # small window relative to n
    if k < 1:
        k = 1
    if k > n:
        k = n

    # Value distribution: cover negatives, zero, duplicates, and large magnitudes.
    vals = []
    for _ in range(n):
        choice = rng.random()
        if choice < 0.20:
            v = rng.choice([-1000000000, 1000000000, -1, 0, 1])   # boundary-ish
        elif choice < 0.35:
            v = rng.randint(-3, 3)                                 # small incl. duplicates
        elif choice < 0.50:
            v = 0                                                  # zeros
        else:
            v = rng.randint(-1000000000, 1000000000)              # full range
        vals.append(v)

    # Occasionally force structured arrays (monotone / constant) to stress edges.
    struct = rng.random()
    if struct < 0.10 and n >= 2:
        # strictly increasing
        vals = sorted(set(rng.randint(-50, 50) for _ in range(200)))[:n]
        while len(vals) < n:
            vals.append(vals[-1] + 1)
        vals = vals[:n]
    elif struct < 0.20 and n >= 2:
        # strictly decreasing
        vals = sorted(set(rng.randint(-50, 50) for _ in range(200)), reverse=True)[:n]
        while len(vals) < n:
            vals.append(vals[-1] - 1)
        vals = vals[:n]
    elif struct < 0.30 and n >= 1:
        # all equal
        c = rng.randint(-1000000000, 1000000000)
        vals = [c] * n

    out = [f"{n} {k}"]
    out.append(" ".join(str(v) for v in vals))
    sys.stdout.write("\n".join(out) + "\n")


main()
