import sys
from random import Random

def gen_one(rng):
    # Keep walkable cells small enough for brute-force bitmask minimax.
    # Bias toward small boards / higher dirty density.
    mode = rng.randint(0, 3)
    if mode == 0:
        # tiny board, can be all-walkable
        N = rng.randint(1, 4)
        M = rng.randint(1, 4)
        pdirty = 0.15
    elif mode == 1:
        # small board, moderate dirty
        N = rng.randint(1, 6)
        M = rng.randint(1, 6)
        pdirty = 0.4
    elif mode == 2:
        # medium board, high dirty
        N = rng.randint(4, 8)
        M = rng.randint(4, 8)
        pdirty = 0.7
    else:
        # larger board, very high dirty (sparse walkable)
        N = rng.randint(5, 8)
        M = rng.randint(5, 8)
        pdirty = 0.85
    grid = [['#' if rng.random() < pdirty else '.' for _ in range(M)] for _ in range(N)]
    ki = rng.randint(0, N - 1)
    kj = rng.randint(0, M - 1)
    grid[ki][kj] = 'K'
    # Guarantee K has at least one walkable neighbor sometimes blocked;
    # but ensure total walkable <= 20 by resampling if too large.
    walkable = sum(1 for row in grid for x in row if x in '.K')
    return N, M, grid, walkable

def main():
    seed = int(sys.argv[1])
    rng = Random(seed)
    T = rng.randint(1, 6)
    out = [str(T)]
    for _ in range(T):
        N, M, grid, walkable = gen_one(rng)
        tries = 0
        while walkable > 20 and tries < 50:
            N, M, grid, walkable = gen_one(rng)
            tries += 1
        # If still too large, force-shrink by adding dirt
        while walkable > 20:
            i = rng.randint(0, N - 1)
            j = rng.randint(0, M - 1)
            if grid[i][j] == '.':
                grid[i][j] = '#'
                walkable -= 1
        out.append(f"{N} {M}")
        for row in grid:
            out.append(''.join(row))
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    main()
