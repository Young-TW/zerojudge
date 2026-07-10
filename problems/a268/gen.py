import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    r = rng.random()
    if r < 0.12:
        N = 1
    elif r < 0.24:
        N = 2
    elif r < 0.36:
        N = 3
    else:
        N = rng.randint(1, 10)

    r2 = rng.random()
    if r2 < 0.15:
        start = [rng.randint(1, 3) for _ in range(N)]
        target = list(start)
    elif r2 < 0.30:
        a = rng.randint(1, 3)
        b = rng.randint(1, 3)
        while b == a:
            b = rng.randint(1, 3)
        start = [a] * N
        target = [b] * N
    else:
        start = [rng.randint(1, 3) for _ in range(N)]
        target = [rng.randint(1, 3) for _ in range(N)]

    out = [str(N)]
    out.append(" ".join(map(str, start)))
    out.append(" ".join(map(str, target)))
    out.append("0")
    sys.stdout.write("\n".join(out) + "\n")


main()
