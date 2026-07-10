import sys
import random

def main():
    rng = random.Random(int(sys.argv[1]))
    mode = rng.randint(0, 4)
    if mode == 0:
        n = 1
        m = 1
    elif mode == 1:
        n = 1
        m = rng.randint(1, 5)
    elif mode == 2:
        n = rng.randint(1, 5)
        m = 1
    elif mode == 3:
        n = rng.randint(1, 4)
        m = rng.randint(1, 4)
    else:
        n = rng.randint(1, 3)
        m = rng.randint(1, 6)
        if n * m > 18:
            n = 3
            m = 6
        if n * m > 18:
            n = 2
            m = 6
    cells = [(x, y) for x in range(1, n + 1) for y in range(1, m + 1)]
    maxk = min(len(cells), rng.randint(0, len(cells)))
    if len(cells) <= 10:
        k = rng.randint(0, maxk)
    else:
        k = rng.randint(0, maxk)
    chosen = rng.sample(cells, k)
    lines = ["%d %d %d" % (n, m, k)]
    for (x, y) in chosen:
        c = rng.randint(0, 1)
        lines.append("%d %d %d" % (x, y, c))
    sys.stdout.write("\n".join(lines) + "\n")

if __name__ == "__main__":
    main()
