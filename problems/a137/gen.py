import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    n = rng.randint(1, 7)

    if n == 1:
        print("1 0")
        return

    max_edges = n * (n - 1) // 2
    min_edges = n - 1  # spanning tree => connected

    # Occasionally force specific densities to cover edge cases
    choice = rng.random()
    if choice < 0.20:
        m = min_edges            # tree
    elif choice < 0.35:
        m = max_edges            # complete graph
    else:
        m = rng.randint(min_edges, max_edges)

    # Build connected graph: start with random spanning tree
    order = list(range(1, n + 1))
    rng.shuffle(order)
    edges = set()
    for i in range(1, n):
        j = rng.randint(0, i - 1)
        a, b = order[i], order[j]
        if a > b:
            a, b = b, a
        edges.add((a, b))

    # Add extra random edges
    remaining = []
    for a in range(1, n + 1):
        for b in range(a + 1, n + 1):
            if (a, b) not in edges:
                remaining.append((a, b))
    rng.shuffle(remaining)
    extra = m - min_edges
    for i in range(min(extra, len(remaining))):
        edges.add(remaining[i])

    # Sometimes use all-1 weights to maximise shortest-path counts
    if rng.random() < 0.30:
        w_lo, w_hi = 1, 1
    else:
        w_lo, w_hi = 1, 20

    edge_list = []
    for (a, b) in edges:
        c = rng.randint(w_lo, w_hi)
        edge_list.append((a, b, c))
    rng.shuffle(edge_list)

    out = [f"{n} {len(edge_list)}"]
    for (a, b, c) in edge_list:
        out.append(f"{a} {b} {c}")
    print("\n".join(out))

main()
