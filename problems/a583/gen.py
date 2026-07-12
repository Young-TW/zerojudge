import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    mode = rng.randint(0, 7)

    if mode == 0:
        # Boundary: smallest N, smallest m
        n = 5
        m = 3
    elif mode == 1:
        # Boundary: smallest N, largest m
        n = 5
        m = 20
    elif mode == 2:
        # Boundary: largest N, smallest m
        n = 100
        m = 3
    elif mode == 3:
        # Boundary: largest N, largest m
        n = 100
        m = 20
    elif mode == 4:
        # Small N, small m, small coordinate range (likely close points)
        n = rng.randint(5, 10)
        m = rng.randint(3, 6)
    elif mode == 5:
        # Tight coordinate range so many points cluster together
        n = rng.randint(5, 20)
        m = rng.randint(5, 12)
    elif mode == 6:
        # General small random
        n = rng.randint(5, 30)
        m = rng.randint(3, 12)
    else:
        # Tiny N with m close to N*N to stress point density
        n = rng.randint(5, 8)
        cap = n * n
        m = rng.randint(min(3, cap), min(20, cap))

    # Coordinates are positive integers in [1, n]. Pick distinct seats.
    coords = []
    seen = set()
    while len(coords) < m:
        x = rng.randint(1, n)
        y = rng.randint(1, n)
        if (x, y) in seen:
            continue
        seen.add((x, y))
        coords.append((x, y))

    flat = []
    for (x, y) in coords:
        flat.append(str(x))
        flat.append(str(y))

    sys.stdout.write("{0} {1}\n".format(n, m))
    sys.stdout.write(" ".join(flat) + "\n")


main()
