#!/usr/bin/env python3
import sys, random

def gen_one_case(rnd, seed):
    if seed == 0:
        m = 1
        grid = [[0]]
    elif seed == 1:
        m = 1
        grid = [[100]]
    elif seed == 2:
        m = 8
        grid = [[7] * 8 for _ in range(8)]
    else:
        m = rnd.randint(1, 8)
        grid = [[rnd.randint(0, 100) for _ in range(m)] for _ in range(m)]
    return m, grid

def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: gen.py <seed>")
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    # number of test cases
    if seed <= 2:
        n = 1
    else:
        n = rnd.randint(1, 5)

    out_lines = [str(n)]
    for _ in range(n):
        m, grid = gen_one_case(rnd, seed)
        out_lines.append(str(m))
        for row in grid:
            out_lines.append(' '.join(map(str, row)))
        out_lines.append('')  # blank line after each case

    sys.stdout.write('\n'.join(out_lines))

if __name__ == "__main__":
    main()
