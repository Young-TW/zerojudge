import sys
import random


def main():
    if len(sys.argv) < 2:
        sys.exit("usage: a067_gen.py <seed>")
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    mode = rng.randint(0, 4)
    if mode == 0:
        # general small
        N = rng.randint(1, 400)
        M = rng.randint(1, 5)
    elif mode == 1:
        # tiny, fine-grained
        N = rng.randint(1, 25)
        M = rng.randint(1, 4)
    elif mode == 2:
        # single layer boundary
        M = 1
        N = rng.randint(1, 100)
    elif mode == 3:
        # small N, multi-layer -> often no solution (boundary)
        M = rng.randint(2, 4)
        N = rng.randint(1, 12)
    else:
        # larger N, small M (brute still fast)
        N = rng.randint(1, 700)
        M = rng.randint(2, 4)

    print(N)
    print(M)


main()
