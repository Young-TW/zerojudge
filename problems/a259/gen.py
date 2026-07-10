import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Small N so brute force runs well within 1 second.
    # N >= 2 guaranteed by the problem (1 < N).
    N = rng.randint(2, 10)

    max_edges = N * (N - 1) // 2
    # M can be 0 (disconnected / no edges) up to a complete graph.
    M = rng.randint(0, max_edges)

    possible = []
    for i in range(1, N + 1):
        for j in range(i + 1, N + 1):
            possible.append((i, j))
    rng.shuffle(possible)
    chosen = possible[:M]

    # Sometimes use small distances to create ties in shortest-path values
    # (interesting edge cases); otherwise use the full allowed range.
    if rng.random() < 0.3:
        dmax = 5
    else:
        dmax = 1000000

    out = ["{} {}".format(N, M)]
    for (a, b) in chosen:
        d = rng.randint(1, dmax)
        out.append("{} {} {}".format(a, b, d))
    out.append("0")  # terminator
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
