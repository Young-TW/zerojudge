import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Small scale so brute (per-query O(N^2)) finishes well under 1s,
    # but enough to exercise edges/deletions/disconnection.
    N = rng.choice([1, 2, 3, rng.randint(2, 8)])
    # simple undirected graph: at most N*(N-1)/2 edges, no self-loops
    max_edges = N * (N - 1) // 2
    M = rng.randint(0, max_edges)

    all_pairs = [(u, v) for u in range(1, N + 1) for v in range(u + 1, N + 1)]
    rng.shuffle(all_pairs)
    chosen = all_pairs[:M]

    # edge weights: include 0, small ints, and a few larger ones
    def rand_w():
        return rng.choice([0, 1, 2, rng.randint(0, 5), rng.randint(0, 20)])

    edges = [(u, v, rand_w()) for (u, v) in chosen]

    # Tasks: ensure deletions only target live edges.
    live = {(min(u, v), max(u, v)) for (u, v, _w) in edges}
    live_list = list(live)

    Q = rng.randint(1, 30)
    ops = []
    for _ in range(Q):
        # bias toward deletes when live edges remain; cover both kinds
        if live_list and rng.random() < 0.45:
            idx = rng.randrange(len(live_list))
            (u, v) = live_list.pop(idx)
            ops.append((2, u, v))
        else:
            a = rng.randint(1, N)
            b = rng.randint(1, N)
            ops.append((1, a, b))

    # Guarantee at least one query of each kind if possible.
    has_q1 = any(o[0] == 1 for o in ops)
    has_q2 = any(o[0] == 2 for o in ops)
    if not has_q1:
        a = rng.randint(1, N)
        b = rng.randint(1, N)
        ops.append((1, a, b))
    if not has_q2 and live:
        (u, v) = live.pop() if hasattr(live, "pop") else live_list.pop()
        if isinstance((u, v), tuple):
            ops.append((2, u, v))

    out = []
    out.append(f"{N} {M} {len(ops)}")
    for (u, v, w) in edges:
        out.append(f"{u} {v} {w}")
    for (k, a, b) in ops:
        out.append(f"{k} {a} {b}")
    sys.stdout.write("\n".join(out) + "\n")


main()
