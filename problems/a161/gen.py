import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Small grid so brute force finishes well under 1s, but covers edges
    # like 1xN, Nx1, corners, full furniture, etc.
    N = rng.randint(1, 8)
    M = rng.randint(1, 8)

    density = rng.choice([0.0, 0.1, 0.3, 0.5, 0.7, 0.9])
    grid = []
    for _ in range(N):
        row = []
        for _ in range(M):
            row.append('x' if rng.random() < density else '.')
        grid.append(row)

    empties = [(i, j) for i in range(N) for j in range(M) if grid[i][j] == '.']
    if not empties:
        i = rng.randint(0, N - 1)
        j = rng.randint(0, M - 1)
        grid[i][j] = '.'
        empties = [(i, j)]
    sx, sy = rng.choice(empties)

    # K continuous intervals covering [1, T], s1 = 1, tK = T.
    K = rng.randint(1, 5)
    intervals = []
    cur = 1
    for _ in range(K):
        length = rng.randint(1, 5)
        d = rng.randint(1, 4)
        intervals.append((cur, cur + length - 1, d))
        cur += length

    out = []
    out.append(f"{N} {M} {sx + 1} {sy + 1} {K}")
    for row in grid:
        out.append(''.join(row))
    for (s, t, d) in intervals:
        out.append(f"{s} {t} {d}")
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
