import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep n small so brute (enumerating C(n-1,k-1) edge cuts) runs <1s.
    r = rng.randint(0, 6)
    if r == 0:
        n = 1
    elif r == 1:
        n = 2
    elif r == 2:
        n = rng.randint(3, 6)
    elif r == 3:
        n = rng.randint(7, 10)
    elif r == 4:
        n = rng.randint(11, 15)
    elif r == 5:
        n = rng.randint(1, 12)
    else:
        n = rng.randint(1, 8)

    k = rng.randint(1, n)

    lines = []
    lines.append("{} {}".format(n, k))

    # loli values: cover boundary 1, small, and occasionally large
    loli = []
    for _ in range(n):
        roll = rng.randint(0, 4)
        if roll == 0:
            v = 1
        elif roll == 1:
            v = rng.randint(1, 10)
        elif roll == 2:
            v = rng.randint(1, 100)
        elif roll == 3:
            v = rng.randint(1, 1000)
        else:
            v = rng.randint(1, 100000000)
        loli.append(v)
    lines.append(" ".join(str(v) for v in loli))

    # Generate a random tree with variety of shapes
    tree_type = rng.randint(0, 3)
    edges = []
    if n == 1:
        pass
    elif tree_type == 0:
        # Random tree: node i connects to random earlier node
        for i in range(2, n + 1):
            p = rng.randint(1, i - 1)
            edges.append((p, i))
    elif tree_type == 1:
        # Bamboo (path) 1-2-3-...-n
        for i in range(2, n + 1):
            edges.append((i - 1, i))
    elif tree_type == 2:
        # Star: node 1 is center
        for i in range(2, n + 1):
            edges.append((1, i))
    else:
        # Caterpillar: path backbone with random leaves
        backbone = max(2, n // 2)
        for i in range(2, backbone + 1):
            edges.append((i - 1, i))
        for i in range(backbone + 1, n + 1):
            p = rng.randint(1, backbone)
            edges.append((p, i))

    # Shuffle edge order and randomly swap endpoints
    rng.shuffle(edges)
    for u, v in edges:
        if rng.randint(0, 1) == 0:
            lines.append("{} {}".format(u, v))
        else:
            lines.append("{} {}".format(v, u))

    sys.stdout.write("\n".join(lines) + "\n")


main()
