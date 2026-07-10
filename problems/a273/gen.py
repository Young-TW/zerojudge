import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    mode = rng.randint(0, 4)
    if mode == 0:
        # boundary: n = 0 (already at step 0)
        n = 0
        k = rng.randint(0, 200)
    elif mode == 1:
        # boundary: k = 0, n > 0 (cannot move)
        n = rng.randint(1, 200)
        k = 0
    elif mode == 2:
        # n divisible by k -> Ok path
        k = rng.randint(1, 200)
        n = rng.randint(0, 5) * k
    elif mode == 3:
        # n not divisible by k -> impossible path
        k = rng.randint(2, 200)
        q = rng.randint(0, 5)
        n = q * k + rng.randint(1, k - 1)
    else:
        # fully random small
        n = rng.randint(0, 200)
        k = rng.randint(0, 200)
    print(n, k)


if __name__ == "__main__":
    main()
