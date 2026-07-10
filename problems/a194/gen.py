import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    cases = []

    # Edge: N = 1
    cases.append([rng.randint(1, 2147483647)])

    # Edge: N = 2, increasing
    a, b = sorted(rng.sample(range(1, 1000), 2))
    cases.append([a, b])

    # Edge: N = 2, decreasing
    a, b = sorted(rng.sample(range(1, 1000), 2), reverse=True)
    cases.append([a, b])

    # Edge: N = 2, equal
    v = rng.randint(1, 2147483647)
    cases.append([v, v])

    # Strictly increasing
    n = rng.randint(5, 20)
    cases.append(list(range(1, n + 1)))

    # Strictly decreasing
    n = rng.randint(5, 20)
    cases.append(list(range(n, 0, -1)))

    # All same values
    n = rng.randint(3, 20)
    v = rng.randint(1, 1000)
    cases.append([v] * n)

    # Random small values (likely duplicates)
    n = rng.randint(10, 50)
    cases.append([rng.randint(1, 5) for _ in range(n)])

    # Many duplicates (only 1, 2, 3)
    n = rng.randint(10, 50)
    cases.append([rng.randint(1, 3) for _ in range(n)])

    # Random medium values
    n = rng.randint(10, 50)
    cases.append([rng.randint(1, 10000) for _ in range(n)])

    # Random large values (up to max)
    n = rng.randint(10, 50)
    cases.append([rng.randint(1, 2147483647) for _ in range(n)])

    # Edge values mixed (1, INT_MAX, or small random)
    n = rng.randint(10, 50)
    vals = []
    for _ in range(n):
        r = rng.randint(1, 3)
        if r == 1:
            vals.append(1)
        elif r == 2:
            vals.append(2147483647)
        else:
            vals.append(rng.randint(1, 100))
    cases.append(vals)

    # Larger random case
    n = rng.randint(50, 200)
    cases.append([rng.randint(1, 1000000) for _ in range(n)])

    # Boundary: N = 500
    n = 500
    cases.append([rng.randint(1, 2147483647) for _ in range(n)])

    # Output
    lines = []
    for case in cases:
        lines.append(str(len(case)))
        lines.append(' '.join(map(str, case)))
    print('\n'.join(lines))


main()
