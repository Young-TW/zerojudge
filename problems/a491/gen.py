import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Edge cases first (exhaustively), then small random cases.
    # Kept small so the brute force runs well under 1 second.
    edge_cases = [
        # 1x1 single cell
        [[5]],
        # 1x1 zero cell
        [[0]],
        # 1xC single row
        [[4, 2, 0, 1, 3]],
        # Rx1 single column
        [[7], [0], [2], [9]],
        # all zeros 3x3
        [[0, 0, 0], [0, 0, 0], [0, 0, 0]],
        # one big value in corner
        [[100000, 0], [0, 0]],
        # 2x2 with tie (lexicographic tiebreak matters)
        [[1, 1], [1, 1]],
        # 2x3 single heavy corner
        [[0, 0, 0], [0, 0, 100000]],
        # 3x3 mixed
        [[4, 2, 0], [0, 1, 1], [1, 0, 0]],
    ]

    cases = [list(m) for m in edge_cases]

    # Add a handful of small random matrices.
    max_rand = 8
    for _ in range(max_rand):
        R = rng.randint(1, 8)
        C = rng.randint(1, 8)
        m = [[rng.randint(0, 10) for _ in range(C)] for _ in range(R)]
        cases.append(m)

    # Occasionally stress with larger value range (still small dims).
    for _ in range(3):
        R = rng.randint(1, 6)
        C = rng.randint(1, 6)
        m = [[rng.randint(0, 100000) for _ in range(C)] for _ in range(R)]
        cases.append(m)

    # One near-worst-size random case to push brute timing a bit
    # (still tiny: 10x10 => 10^4 cells, brute is ~10^8 ops worst -> ok in 1s).
    R = rng.randint(8, 10)
    C = rng.randint(8, 10)
    m = [[rng.randint(0, 100) for _ in range(C)] for _ in range(R)]
    cases.append(m)

    out = []
    out.append(str(len(cases)))
    for m in cases:
        out.append("%d %d" % (len(m), len(m[0])))
        for row in m:
            out.append(" ".join(str(x) for x in row))
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()
