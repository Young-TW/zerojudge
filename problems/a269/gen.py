#!/usr/bin/env python3
# Test case generator for ZeroJudge a269 (小氣的國王).
# Usage: python3 a269_gen.py <seed>
# Prints one valid random input (multiple cases + "0 0" terminator) to stdout,
# reproducible from the seed.
#
# Problem: n cities, m proposed bidirectional roads (length d, cost c). Keep a
# subset of roads so that the shortest distance from city 1 to every city is
# unchanged; minimize total cost of kept roads.
#
# Scale kept small (n <= 8, m <= 16) so the 2^m brute force finishes in <1s.
# Guarantees city 1 can reach all cities (builds a spanning tree first, then
# adds extra edges). Covers boundaries: n=1, single edge, trees, complete
# graphs, multiple shortest paths, parallel edges, extreme d/c values.

import sys
import random


def gen_edge(rng, n, seen, allow_parallel, d_choices=None, c_choices=None):
    """Generate one edge (u, v, d, c) with u != v, 1 <= u,v <= n."""
    while True:
        u = rng.randint(1, n)
        v = rng.randint(1, n)
        if u == v:
            continue
        a, b = (u, v) if u < v else (v, u)
        if not allow_parallel and (a, b) in seen:
            continue
        seen.add((a, b))
        break
    d = rng.choice(d_choices) if d_choices else rng.randint(1, 10000)
    c = rng.choice(c_choices) if c_choices else rng.randint(1, 1000)
    return (u, v, d, c)


def build_tree(rng, n, d_choices=None, c_choices=None):
    """Build a random spanning tree rooted at city 1. Returns (edges, seen)."""
    edges = []
    seen = set()
    for v in range(2, n + 1):
        u = rng.randint(1, v - 1)
        a, b = (u, v) if u < v else (v, u)
        seen.add((a, b))
        d = rng.choice(d_choices) if d_choices else rng.randint(1, 10000)
        c = rng.choice(c_choices) if c_choices else rng.randint(1, 1000)
        edges.append((u, v, d, c))
    return edges, seen


def main():
    rng = random.Random(int(sys.argv[1]))

    n_cases = rng.randint(1, 4)
    out_lines = []

    for _ in range(n_cases):
        scenario = rng.randint(0, 9)
        edges = []

        if scenario == 0:
            # n=1: trivially answer 0, no edges possible
            n = 1
        elif scenario == 1:
            # n=2, single edge
            n = 2
            edges = [(1, 2, rng.randint(1, 10000), rng.randint(1, 1000))]
        elif scenario == 2:
            # small tree, n=3..5
            n = rng.randint(3, 5)
            edges, _ = build_tree(rng, n)
        elif scenario == 3:
            # tree + extra random edges, n=4..7
            n = rng.randint(4, 7)
            edges, seen = build_tree(rng, n)
            max_extra = min(16 - len(edges), n * (n - 1) // 2 - len(seen))
            for _ in range(rng.randint(0, max(0, max_extra))):
                edges.append(gen_edge(rng, n, seen, allow_parallel=False))
        elif scenario == 4:
            # complete graph small, n=4..5
            n = rng.randint(4, 5)
            seen = set()
            for u in range(1, n + 1):
                for v in range(u + 1, n + 1):
                    edges.append((u, v, rng.randint(1, 10000),
                                  rng.randint(1, 1000)))
                    seen.add((u, v))
        elif scenario == 5:
            # uniform d, varying c -> multiple shortest paths
            n = rng.randint(3, 6)
            d_val = rng.randint(1, 10)
            edges, seen = build_tree(rng, n, d_choices=[d_val])
            max_extra = min(16 - len(edges), n * (n - 1) // 2 - len(seen))
            for _ in range(rng.randint(0, max(0, max_extra))):
                edges.append(gen_edge(rng, n, seen, allow_parallel=False,
                                      d_choices=[d_val]))
        elif scenario == 6:
            # random connected graph, n=5..8
            n = rng.randint(5, 8)
            edges, seen = build_tree(rng, n)
            max_extra = min(16 - len(edges), n * (n - 1) // 2 - len(seen))
            for _ in range(rng.randint(0, max(0, max_extra))):
                edges.append(gen_edge(rng, n, seen, allow_parallel=False))
        elif scenario == 7:
            # extreme d and c values
            n = rng.randint(2, 6)
            edges, seen = build_tree(rng, n, d_choices=[1, 10000],
                                     c_choices=[1, 1000])
            max_extra = min(16 - len(edges), n * (n - 1) // 2 - len(seen))
            for _ in range(rng.randint(0, max(0, max_extra))):
                edges.append(gen_edge(rng, n, seen, allow_parallel=False,
                                      d_choices=[1, 10000],
                                      c_choices=[1, 1000]))
        elif scenario == 8:
            # path graph 1-2-...-n plus shortcuts
            n = rng.randint(3, 7)
            seen = set()
            for v in range(2, n + 1):
                edges.append((v - 1, v, rng.randint(1, 100),
                              rng.randint(1, 1000)))
                seen.add((v - 1, v))
            max_extra = min(16 - len(edges), n * (n - 1) // 2 - len(seen))
            for _ in range(rng.randint(0, max(0, max_extra))):
                edges.append(gen_edge(rng, n, seen, allow_parallel=False))
        else:
            # parallel edges: same pair, different d/c
            n = rng.randint(2, 5)
            edges, _ = build_tree(rng, n)
            n_parallel = rng.randint(1, min(4, 16 - len(edges)))
            for _ in range(n_parallel):
                if not edges:
                    break
                base = rng.choice(edges)
                edges.append((base[0], base[1], rng.randint(1, 10000),
                              rng.randint(1, 1000)))

        m = len(edges)
        if m > 16:
            edges = edges[:16]
            m = 16

        out_lines.append(f"{n} {m}")
        rng.shuffle(edges)
        for (u, v, d, c) in edges:
            out_lines.append(f"{u} {v} {d} {c}")

    out_lines.append("0 0")
    sys.stdout.write("\n".join(out_lines) + "\n")


if __name__ == "__main__":
    main()
