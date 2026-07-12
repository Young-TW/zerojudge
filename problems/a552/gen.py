import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep n small so the O(n!) brute force finishes well within 1 second.
    n = rng.randint(1, 9)

    # Build a random permutation and only allow edges that go "forward"
    # in permutation order.  This guarantees the graph is a DAG.
    perm = list(range(n))
    rng.shuffle(perm)
    rank = [0] * n
    for i, node in enumerate(perm):
        rank[node] = i

    possible = []
    for u in range(n):
        for v in range(n):
            if rank[u] < rank[v]:
                possible.append((u, v))

    max_m = len(possible)
    m = rng.randint(0, max_m) if max_m > 0 else 0

    rng.shuffle(possible)
    edges = possible[:m]

    out = ["{} {}".format(n, m)]
    for u, v in edges:
        out.append("{} {}".format(u, v))
    print("\n".join(out))


main()
