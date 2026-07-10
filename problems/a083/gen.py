import sys
import random


def main():
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    out = []
    N = rnd.choice([1, 2, 3, 5, 10, 30])
    K = rnd.randint(0, 300)

    out.append(f"{N} {K}")
    for _ in range(K):
        D = rnd.choice([1, 2])
        r = rnd.random()
        if r < 0.05:
            X = rnd.randint(N + 1, N + 5)
        else:
            X = rnd.randint(1, N)
        r2 = rnd.random()
        if r2 < 0.05:
            Y = rnd.randint(N + 1, N + 5)
        elif r2 < 0.10 and D == 2:
            Y = X
        else:
            Y = rnd.randint(1, N)
        out.append(f"{D} {X} {Y}")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
