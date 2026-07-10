import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Small scale so brute force finishes well under 1s, but covers boundaries.
    N = rng.randint(2, 8)
    M = rng.randint(2, N)
    K = rng.randint(1, N)

    # Build a random tree on positions 1..N (position i connects to a parent in 1..i-1),
    # then shuffle labels so node 1 need not be the root, and shuffle edge order.
    perm = list(range(1, N + 1))
    rng.shuffle(perm)

    edges = []
    for i in range(2, N + 1):
        parent = rng.randint(1, i - 1)
        c = rng.randint(0, 100)
        a = perm[parent - 1]
        b = perm[i - 1]
        edges.append((a, b, c))

    rng.shuffle(edges)

    out = []
    out.append(f"{N} {M} {K}")
    for a, b, c in edges:
        out.append(f"{a} {b} {c}")
    sys.stdout.write("\n".join(out) + "\n")


main()
