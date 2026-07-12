import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    n = rng.randint(1, 6)
    lines = [str(n)]
    for _ in range(n):
        if rng.random() < 0.15:
            x = 1
        else:
            x = rng.randint(1, 60)
        y = rng.randint(1, 12)
        t = rng.random()
        if t < 0.25:
            z = y
        elif t < 0.45:
            z = y + rng.randint(1, 5)
        else:
            z = rng.randint(1, 12)
        lines.append("%d %d %d" % (x, y, z))
    sys.stdout.write("\n".join(lines) + "\n")


main()
