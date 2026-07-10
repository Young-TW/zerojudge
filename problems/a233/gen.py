import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep N small so brute-force (bubble sort, O(n^2)) finishes well under 1s.
    # Occasionally hit boundary N=1 and N=2.
    boundary = rng.randint(0, 9)
    if boundary == 0:
        n = 1
    elif boundary == 1:
        n = 2
    else:
        n = rng.randint(1, 2000)

    print(n)

    # Vary value distribution to cover edges: zeros, duplicates, max-range.
    mode = rng.randint(0, 4)
    if mode == 0:
        # all zeros
        vals = [0] * n
    elif mode == 1:
        # tiny range -> many duplicates
        vals = [rng.randint(0, 5) for _ in range(n)]
    elif mode == 2:
        # already-sorted-ish small range
        vals = [rng.randint(0, 100) for _ in range(n)]
    elif mode == 3:
        # wide range including 0 and large values
        vals = [rng.randint(0, 10**9) for _ in range(n)]
    else:
        # sprinkle explicit edge values among random ones
        edges = [0, 1, 10**9]
        vals = [rng.choice(edges) if rng.random() < 0.3 else rng.randint(0, 10**9)
                for _ in range(n)]

    print(' '.join(map(str, vals)))


main()
