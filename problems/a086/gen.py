import sys
import random


def main():
    if len(sys.argv) < 2:
        sys.exit("usage: a086_gen.py <seed>")
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Sizes are kept tiny (N*M <= ~20) so a naive brute finishes well under 1s,
    # while still exercising boundary shapes and the max M=10.
    mode = rng.randint(0, 7)
    if mode == 0:
        # general small mixed
        N = rng.randint(1, 4)
        M = rng.randint(1, 5)
    elif mode == 1:
        # very tiny, fine-grained
        N = rng.randint(1, 3)
        M = rng.randint(1, 4)
    elif mode == 2:
        # single row, up to full width M=10
        N = 1
        M = rng.randint(1, 10)
    elif mode == 3:
        # single column
        N = rng.randint(1, 10)
        M = 1
    elif mode == 4:
        # boundary: full width M=10, 1 or 2 rows
        M = 10
        N = rng.randint(1, 2)
    elif mode == 5:
        # all plains (densest -> hardest for brute)
        N = rng.randint(1, 4)
        M = rng.randint(1, 5)
    elif mode == 6:
        # all hills (no placement possible)
        N = rng.randint(1, 5)
        M = rng.randint(1, 5)
    else:
        # mixed, slightly taller
        N = rng.randint(1, 5)
        M = rng.randint(1, 4)

    print(N, M)
    for i in range(N):
        row = []
        for j in range(M):
            if mode == 5:
                row.append('P')
            elif mode == 6:
                row.append('H')
            else:
                row.append('P' if rng.random() < 0.6 else 'H')
        print(''.join(row))


main()
