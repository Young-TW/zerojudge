#!/usr/bin/env python3
import sys, random

def main():
    if len(sys.argv) < 2:
        return
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    if seed == 0:                     # minimal n, all zeros
        n = 2
        board = [[0] * 8 for _ in range(8)]
    elif seed == 1:                   # maximal n, all max values
        n = 14
        board = [[99] * 8 for _ in range(8)]
    elif seed == 2:                   # single non‑zero element
        n = rng.randint(2, 14)
        board = [[0] * 8 for _ in range(8)]
        i, j = rng.randrange(8), rng.randrange(8)
        board[i][j] = rng.randint(1, 99)
    else:                             # general random case
        n = rng.randint(2, 14)
        board = [[rng.randint(0, 99) for _ in range(8)] for _ in range(8)]

    out_lines = [str(n)]
    out_lines += [' '.join(str(v) for v in row) for row in board]
    sys.stdout.write('\n'.join(out_lines))

if __name__ == "__main__":
    main()
