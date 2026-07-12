import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep n, m small so brute-force enumeration runs well under 1s.
    # Worst case ~ C(n+m-1, m) tuples; with n<=8, m<=12 that is at most
    # C(19,12)=50388, easily fast enough.
    r = rng.randint(0, 6)
    if r == 0:
        n = 1                      # single type
    elif r == 1:
        n = 2                      # minimal multi-type
    elif r == 2:
        n = rng.randint(1, 4)      # tiny
    elif r == 3:
        n = rng.randint(5, 8)      # small
    elif r == 4:
        n = rng.randint(1, 8)      # random small
    else:
        n = rng.randint(1, 8)

    # m boundaries: 1, small, and up to 12
    mr = rng.randint(0, 3)
    if mr == 0:
        m = 1
    elif mr == 1:
        m = rng.randint(1, 4)
    elif mr == 2:
        m = rng.randint(5, 12)
    else:
        m = rng.randint(1, 12)

    a = []
    for _ in range(n):
        roll = rng.randint(0, 5)
        if roll == 0:
            v = 0                  # type cannot be used
        elif roll == 1:
            v = 1                  # at most one
        elif roll == 2:
            v = m                  # exactly enough for all
        elif roll == 3:
            v = m + rng.randint(0, 3)  # more than enough
        elif roll == 4:
            v = rng.randint(0, max(0, m - 1))  # scarce
        else:
            v = rng.randint(0, m + 2)
        a.append(v)

    lines = []
    lines.append("{} {}".format(n, m))
    lines.append(" ".join(str(v) for v in a))
    sys.stdout.write("\n".join(lines) + "\n")


main()
