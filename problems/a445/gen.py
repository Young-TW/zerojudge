import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Small scale so brute (BFS per query) runs well under 1s, but cover edges.
    # N up to ~60, M up to ~80, Q up to ~200.
    N = rng.randint(1, 60)
    M = rng.randint(0, 80)
    Q = rng.randint(1, 200)
    print(N, M, Q)

    # Generate friend edges. Allow duplicates and self-loops occasionally to
    # cover boundary behavior; values stay within [1, N].
    for _ in range(M):
        a = rng.randint(1, N)
        b = rng.randint(1, N)
        print(a, b)

    # Generate queries, including same-person query occasionally.
    for _ in range(Q):
        p = rng.randint(1, N)
        q = rng.randint(1, N)
        if rng.random() < 0.1:
            q = p
        print(p, q)


main()
