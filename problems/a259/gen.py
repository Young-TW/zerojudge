import sys, random

def main():
    if len(sys.argv) < 2:
        return
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Corner cases for small seeds
    if seed == 0:
        # Minimal graph: N=2, no edges
        N, M = 2, 0
        edges = []
    elif seed == 1:
        # Single edge with maximal weight
        N, M = 2, 1
        edges = [(1, 2, 1000000)]
    elif seed == 2:
        # Large N with a simple line tree, all weights equal
        N = 1000
        M = N - 1
        edges = [(i, i + 1, 1) for i in range(1, N)]
    else:
        # General random case
        N = rng.randint(2, 1000)
        max_edges = N * (N - 1) // 2
        # keep output reasonable; cap at 5000 edges for large N
        cap = min(max_edges, 5000)
        M = rng.randint(0, cap)
        edge_set = set()
        edges = []
        while len(edges) < M:
            a = rng.randint(1, N)
            b = rng.randint(1, N)
            if a == b:
                continue
            if a > b:
                a, b = b, a
            if (a, b) in edge_set:
                continue
            edge_set.add((a, b))
            d = rng.randint(1, 1000000)
            edges.append((a, b, d))

    out_lines = [f"{N} {M}"]
    out_lines += [f"{a} {b} {d}" for a, b, d in edges]
    out_lines.append("0")
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()
