import sys
import random


def main():
    if len(sys.argv) < 2:
        sys.stderr.write("usage: a304_gen.py <seed>\n")
        sys.exit(1)
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    n = rnd.randint(2, 6)
    m = rnd.randint(1, 8)
    k = rnd.randint(0, 6)

    D = [rnd.randint(1, 4) for _ in range(n - 1)]

    passengers = []
    for _ in range(m):
        t = rnd.randint(0, 12)
        a = rnd.randint(1, n - 1)
        b = rnd.randint(a + 1, n)
        passengers.append((t, a, b))

    out = []
    out.append(f"{n} {m} {k}")
    out.append(" ".join(map(str, D)))
    for (t, a, b) in passengers:
        out.append(f"{t} {a} {b}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
