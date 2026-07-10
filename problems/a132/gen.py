import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    # Boundary / interesting values for 1 <= I <= 2147483647
    edges = [1, 2, 3, 2147483647, 2147483646, 2147483645,
             1024, 1023, 65536, 5, 7, 8]
    n = rng.randint(1, 8)
    num_edges = rng.randint(0, min(len(edges), n))
    chosen_edges = rng.sample(edges, num_edges)
    values = list(chosen_edges)
    for _ in range(n - num_edges):
        values.append(rng.randint(1, 2147483647))
    rng.shuffle(values)
    out = []
    for v in values:
        out.append(str(v))
    out.append("0")
    sys.stdout.write("\n".join(out) + "\n")


main()
