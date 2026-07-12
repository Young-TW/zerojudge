import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Small T so brute output stays tiny (2^15 subsets each, output grows
    # fast). Cover the boundary N=1 and N=15 explicitly, plus random small N.
    # Weights: edge/boundary cases get dedicated slots, then small random.
    r = rng.random()
    if r < 0.20:
        # boundary N values
        Ns = [1, 15]
    elif r < 0.40:
        # small N around the lower edge
        Ns = [rng.randint(1, 4)]
    elif r < 0.60:
        # a couple of small random N
        T = 2
        Ns = [rng.randint(1, 8) for _ in range(T)]
    elif r < 0.80:
        # single mid-range N
        Ns = [rng.randint(9, 12)]
    else:
        # single small-to-max N, possibly two cases
        T = rng.randint(1, 2)
        Ns = [rng.randint(1, 15) for _ in range(T)]

    T = len(Ns)
    print(T)
    for n in Ns:
        print(n)


main()
