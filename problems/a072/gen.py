import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    n = rng.randint(1, 40)
    L = rng.randint(1, n)
    R = rng.randint(L, n)

    # number of valid intervals = sum_{len=L}^{R} (n - len + 1)
    num_intervals = sum(n - length + 1 for length in range(L, R + 1))
    k = rng.randint(1, max(1, num_intervals))

    out = [f"{n} {k} {L} {R}"]
    for _ in range(n):
        a = rng.randint(-100, 100)
        out.append(str(a))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
