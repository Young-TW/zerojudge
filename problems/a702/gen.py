import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep the number of queries small so the brute (which scans primes
    # from scratch for each query, capped at LIMIT=2e7) stays well under 1s.
    # Each query may force a near-full scan up to ~2e7, so a handful of
    # distinct large-S queries is enough to stress correctness while
    # staying fast.
    r = rng.randint(0, 4)
    if r == 0:
        n = 1
    elif r == 1:
        n = 2
    elif r == 2:
        n = rng.randint(3, 6)
    elif r == 3:
        n = rng.randint(5, 12)
    else:
        n = rng.randint(8, 20)

    lines = []
    for _ in range(n):
        roll = rng.randint(0, 5)
        if roll == 0:
            s = 1  # boundary: first cousin prime
        elif roll == 1:
            s = 2
        elif roll == 2:
            s = 100000  # boundary: last valid cousin prime (< 2e7)
        elif roll == 3:
            s = 99999
        elif roll == 4:
            s = rng.randint(1, 1000)  # small range, easy to verify
        else:
            s = rng.randint(1, 100000)  # full range
        lines.append(str(s))

    sys.stdout.write("\n".join(lines) + "\n")


main()
