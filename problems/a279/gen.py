import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Fixed boundary cases to always exercise edge conditions.
    boundaries = [
        (0, 1, 0),   # m=1 -> trivially divisible
        (0, 1, 5),
        (7, 1, 0),
        (10, 5, 0),  # already divisible, e=0
        (3, 3, 0),
        (0, 7, 10),  # n=0 but m>1: need operations
        (5, 5, 0),   # sample-like, divisible
    ]

    k = rng.randint(8, 20)
    cases = []
    for _ in range(k):
        n = rng.choice([0, 1, rng.randint(0, 60)])
        m = rng.choice([1, 2, 3, rng.randint(1, 60)])
        e = rng.choice([0, 1, 2, 3, rng.randint(0, 25)])
        cases.append((n, m, e))

    # Sprinkle in a fixed boundary case deterministically.
    cases.append(rng.choice(boundaries))

    out = "".join(f"{n} {m} {e}\n" for (n, m, e) in cases)
    sys.stdout.write(out)


main()
