import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    mode = rng.randint(0, 9)

    if mode == 0:
        # Tiny: n in [1, 3], delta in [1, n]. Hits n=1 boundary.
        n = rng.randint(1, 3)
        delta = rng.randint(1, n)
    elif mode == 1:
        # Very small, delta = 1 (forces consecutive only).
        n = rng.randint(1, 8)
        delta = 1
    elif mode == 2:
        # Very small, delta = n (no real gap constraint).
        n = rng.randint(1, 8)
        delta = n
    elif mode == 3:
        # Small with small delta (controlled branching).
        n = rng.randint(4, 12)
        delta = rng.randint(1, 3)
    elif mode == 4:
        # All negative numbers (best answer is a single max element).
        n = rng.randint(1, 12)
        delta = rng.randint(1, n)
        print(n, delta)
        print(' '.join(str(rng.randint(-100, -1)) for _ in range(n)))
        return
    elif mode == 5:
        # All zeros.
        n = rng.randint(1, 12)
        delta = rng.randint(1, n)
        print(n, delta)
        print(' '.join('0' for _ in range(n)))
        return
    elif mode == 6:
        # Mix of large positive and large negative (boundary values near int range).
        n = rng.randint(1, 12)
        delta = rng.randint(1, n)
        print(n, delta)
        print(' '.join(str(rng.choice([2147483647, -2147483648, 0, rng.randint(-50, 50)]))
                       for _ in range(n)))
        return
    elif mode == 7:
        # Single element.
        n = 1
        delta = 1
    elif mode == 8:
        # Two elements, delta covers both boundary cases (1 and 2).
        n = 2
        delta = rng.randint(1, 2)
    else:
        # General small random.
        n = rng.randint(1, 14)
        delta = rng.randint(1, n)

    print(n, delta)
    print(' '.join(str(rng.randint(-50, 50)) for _ in range(n)))


if __name__ == '__main__':
    main()
