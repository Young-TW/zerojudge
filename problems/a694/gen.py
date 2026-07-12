import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # One test case per invocation. Keep n small so O(n*n*m) brute runs <1s.
    r = rng.randint(0, 5)
    if r == 0:
        n = 1
    elif r == 1:
        n = 2
    elif r == 2:
        n = rng.randint(3, 8)
    elif r == 3:
        n = rng.randint(10, 25)
    elif r == 4:
        n = rng.randint(26, 50)
    else:
        n = rng.randint(1, 40)

    m = rng.randint(1, 500)

    lines = []
    lines.append("{} {}".format(n, m))

    # food values: cover boundary 1 and 100 plus random small numbers
    for _ in range(n):
        row = []
        for _ in range(n):
            if rng.randint(0, 2) == 0:
                v = rng.choice([1, 1, 100, 100])
            else:
                v = rng.randint(1, 100)
            row.append(v)
        lines.append(" ".join(str(v) for v in row))

    for _ in range(m):
        # 1 <= x1 <= x2 <= n, 1 <= y1 <= y2 <= n
        # cover boundaries: full grid, single cell, first/last row/col
        roll = rng.randint(0, 5)
        if roll == 0:
            x1, y1, x2, y2 = 1, 1, n, n
        elif roll == 1:
            x1 = rng.randint(1, n)
            y1 = rng.randint(1, n)
            x2, y2 = x1, y1  # single cell
        elif roll == 2:
            x1 = 1
            x2 = rng.randint(1, n)
            y1 = rng.randint(1, n)
            y2 = rng.randint(y1, n)
        elif roll == 3:
            x1 = rng.randint(1, n)
            x2 = n
            y1 = rng.randint(1, n)
            y2 = rng.randint(y1, n)
        elif roll == 4:
            y1 = 1
            y2 = rng.randint(1, n)
            x1 = rng.randint(1, n)
            x2 = rng.randint(x1, n)
        else:
            x1 = rng.randint(1, n)
            x2 = rng.randint(x1, n)
            y1 = rng.randint(1, n)
            y2 = rng.randint(y1, n)
        lines.append("{} {} {} {}".format(x1, y1, x2, y2))

    sys.stdout.write("\n".join(lines) + "\n")


main()
