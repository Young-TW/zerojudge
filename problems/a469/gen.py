import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    pool = "abcdefghijklmnopqrstuvwxyz"
    ncases = rng.randint(1, 3)
    lines = []
    for _ in range(ncases):
        # bias toward small sizes so the brute finishes well within 1s,
        # but still cover the n=1 boundary and order-dependence.
        r = rng.randint(0, 9)
        if r == 0:
            length = 1
        elif r == 1:
            length = 2
        else:
            length = rng.randint(1, 7)
        chars = rng.sample(pool, length)
        lines.append("".join(chars))
    sys.stdout.write("\n".join(lines) + "\n")


main()
