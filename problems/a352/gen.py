import sys
import random


def gen(rng):
    # Choose a "mode" to cover different boundary cases.
    mode = rng.randint(0, 4)

    if mode == 0:
        # Minimal: 2 nodes, 1 resistor.
        n = 2
        edges = [(1, 2, rng.randint(1, 20))]
    elif mode == 1:
        # Pure parallel: 2 nodes, several resistors in parallel.
        n = 2
        k = rng.randint(2, 4)
        edges = [(1, 2, rng.randint(1, 20)) for _ in range(k)]
    elif mode == 2:
        # Series chain 1-2-3-...-n, possibly with extra parallel resistors.
        n = rng.randint(3, 5)
        edges = [(i, i + 1, rng.randint(1, 20)) for i in range(1, n)]
        # maybe add a parallel resistor across an existing edge
        if rng.random() < 0.6:
            i = rng.randint(1, n - 1)
            edges.append((i, i + 1, rng.randint(1, 20)))
    elif mode == 3:
        # Bridge-ish: a small graph with a Wheatstone-bridge-like topology.
        # nodes 1..4, edges forming a bridge plus extra.
        n = rng.randint(4, 6)
        edges = [
            (1, 2, rng.randint(1, 15)),
            (1, 3, rng.randint(1, 15)),
            (2, 3, rng.randint(1, 15)),
            (2, 4, rng.randint(1, 15)),
            (3, 4, rng.randint(1, 15)),
        ]
        # a couple of random extra edges
        extra = rng.randint(0, 2)
        for _ in range(extra):
            a, b = rng.sample(range(1, n + 1), 2)
            edges.append((a, b, rng.randint(1, 15)))
    else:
        # Generic random small graph.
        n = rng.randint(2, 6)
        m = rng.randint(1, 8)
        edges = []
        for _ in range(m):
            a, b = rng.sample(range(1, n + 1), 2)
            edges.append((a, b, rng.randint(1, 25)))

    # Make sure S and T are connected in the underlying graph; otherwise keep
    # adding a random resistor until they are. The problem guarantees a finite
    # positive answer, so connectivity matters for a sensible test.
    s = rng.randint(1, n)
    t = rng.randint(1, n)
    while t == s:
        t = rng.randint(1, n)

    # Ensure connectivity between s and t via union-find.
    def find(parent, x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def connected():
        parent = list(range(n + 1))
        for a, b, _ in edges:
            ra, rb = find(parent, a), find(parent, b)
            if ra != rb:
                parent[ra] = rb
        return find(parent, s) == find(parent, t)

    guard = 0
    while not connected() and guard < 50:
        a, b = rng.sample(range(1, n + 1), 2)
        edges.append((a, b, rng.randint(1, 20)))
        guard += 1
    # Fallback: force a direct resistor s-t if still disconnected.
    if not connected():
        edges.append((s, t, rng.randint(1, 10)))

    return n, edges, s, t


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    rng = random.Random(seed)
    n, edges, s, t = gen(rng)
    m = len(edges)
    out = []
    out.append(f"{n} {m}")
    for a, b, r in edges:
        out.append(f"{a} {b} {r}")
    out.append(f"{s} {t}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
