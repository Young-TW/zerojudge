import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep dimensions tiny so a brute-force flood-fill is instant, but
    # exercise the legal boundaries (5..30 -> use 5..10) and a couple of
    # interesting shapes. We pick A,B in [5, 10].
    A = rng.randint(5, 10)
    B = rng.randint(5, 10)

    # Choose a value palette so that queried heights sometimes:
    #   - exist with large components,
    #   - exist as isolated singletons (-> output 0),
    #   - are absent entirely (-> output 0).
    # Mix a dominant value, a few sparse values, and an all-same grid
    # case occasionally.
    roll = rng.randint(0, 4)
    if roll == 0:
        # All same height -> entire grid is one component.
        vals = [rng.randint(1, 9)]
        palette = [vals[0]]
    elif roll == 1:
        # Two values, biased toward big blocks of one.
        a = rng.randint(1, 9)
        b = rng.randint(1, 9)
        while b == a:
            b = rng.randint(1, 9)
        palette = [a, b]
    else:
        # General mix: 1..9, possibly with some heights unused.
        k = rng.randint(2, 5)
        palette = rng.sample(range(1, 10), k)

    rows = []
    for _ in range(A):
        row = []
        for _ in range(B):
            # Bias to first palette entry to create bigger connected blobs.
            r = rng.randint(0, 3)
            if r == 0 and len(palette) > 1:
                row.append(palette[rng.randint(1, len(palette) - 1)])
            else:
                row.append(palette[0])
        rows.append(row)

    # Build query list: cover palette + at least one absent height + a
    # duplicate to test repeatability.
    present = set()
    for row in rows:
        for v in row:
            present.add(v)
    absent = [h for h in range(1, 10) if h not in present]
    if not absent:
        absent = [rng.randint(1, 9)]

    queries = list(present)
    queries.append(absent[0])
    if len(present) >= 1:
        # duplicate an existing height
        queries.append(next(iter(present)))
    # maybe add a second absent height
    if len(absent) > 1:
        queries.append(absent[1])
    rng.shuffle(queries)
    # keep query count within [1, 9] as per problem statement
    if len(queries) > 9:
        queries = queries[:9]
    if not queries:
        queries = [rng.randint(1, 9)]

    out = []
    out.append("%d %d" % (A, B))
    for row in rows:
        out.append(" ".join(str(v) for v in row))
    out.append(str(len(queries)))
    for q in queries:
        out.append(str(q))
    sys.stdout.write("\n".join(out) + "\n")


main()
