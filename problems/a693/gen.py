import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # One test case per invocation. Keep n small so O(n*m) brute runs <1s.
    r = rng.randint(0, 5)
    if r == 0:
        n = 1
    elif r == 1:
        n = 2
    elif r == 2:
        n = rng.randint(3, 8)
    elif r == 3:
        n = rng.randint(20, 50)
    elif r == 4:
        n = rng.randint(100, 300)
    else:
        n = rng.randint(1, 200)

    m = rng.randint(1, min(n, 300))

    lines = []
    lines.append("{} {}".format(n, m))

    # food values: cover boundary 1 and 1000 plus random small numbers
    food = []
    for _ in range(n):
        if rng.randint(0, 2) == 0:
            v = rng.choice([1, 1, 1000, 1000])
        else:
            v = rng.randint(1, 1000)
        food.append(v)
    lines.append(" ".join(str(v) for v in food))

    for _ in range(m):
        # 1 <= l <= r <= n; cover boundary l==1, r==n, l==r
        roll = rng.randint(0, 3)
        if roll == 0:
            l = 1
            r = n
        elif roll == 1:
            l = rng.randint(1, n)
            r = l  # single-element query
        elif roll == 2:
            l = 1
            r = rng.randint(1, n)
        else:
            l = rng.randint(1, n)
            r = rng.randint(l, n)
        lines.append("{} {}".format(l, r))

    sys.stdout.write("\n".join(lines) + "\n")


main()
