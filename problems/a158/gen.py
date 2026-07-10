import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # number of test cases; problem says 1 < N < 100, keep small for brute force
    N = rng.randint(1, 8)
    print(N)

    for _ in range(N):
        # numbers per line; problem says 1 < M < 100, keep small
        M = rng.randint(2, 15)
        mode = rng.randint(0, 3)
        if mode == 0:
            # boundary-ish: all identical -> GCD is the number itself
            base = rng.randint(1, 100000)
            nums = [base] * M
        elif mode == 1:
            # all multiples of a common factor -> forces large GCDs
            g = rng.randint(1, 1000)
            nums = [g * rng.randint(1, 100) for _ in range(M)]
        elif mode == 2:
            # small numbers, often includes 1 -> small/noisy GCDs
            nums = [rng.randint(1, 50) for _ in range(M)]
        else:
            # general random, wide range
            nums = [rng.randint(1, 1000000) for _ in range(M)]
        print(' '.join(map(str, nums)))


if __name__ == "__main__":
    main()
