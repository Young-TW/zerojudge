import sys, random

def main():
    if len(sys.argv) != 2:
        return
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    # ---- corner cases for small seeds ----
    if seed == 0:
        N, M = 2, 1
        edges = [(1, 2, 1)]
    elif seed == 1:
        N, M = 2, 1
        edges = [(1, 2, 100000)]
    elif seed == 2:
        N = 1000
        M = N - 1
        edges = [(i, i + 1, 1) for i in range(1, N)]
    else:
        # ---- general case ----
        N = rnd.randint(2, 1000)
        max_possible = N * (N - 1) // 2
        maxM = min(100000, max_possible)
        M = rnd.randint(N - 1, maxM)

        edges = []
        # build a random spanning tree
        nodes = list(range(1, N + 1))
        rnd.shuffle(nodes)
        for i in range(1, N):
            u = nodes[i]
            v = nodes[rnd.randint(0, i - 1)]
            w = rnd.randint(1, 100000)
            edges.append((u, v, w))

        existing = set()
        for u, v, _ in edges:
            a, b = (u, v) if u < v else (v, u)
            existing.add((a, b))

        # add extra random edges
        while len(edges) < M:
            u = rnd.randint(1, N)
            v = rnd.randint(1, N)
            if u == v:
                continue
            a, b = (u, v) if u < v else (v, u)
            if (a, b) in existing:
                continue
            w = rnd.randint(1, 100000)
            edges.append((u, v, w))
            existing.add((a, b))

    # ---- output ----
    out_lines = [f"{N} {M}"]
    out_lines += [f"{u} {v} {w}" for u, v, w in edges]
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()
