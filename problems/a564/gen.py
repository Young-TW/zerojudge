import sys
from random import Random

def main():
    if len(sys.argv) < 2:
        sys.stderr.write("usage: a564_gen.py <seed>\n")
        sys.exit(1)
    rng = Random(int(sys.argv[1]))

    # Pick a structure family to exercise different shapes.
    family = rng.randint(0, 4)

    if family == 0:
        # Minimum n.
        n = 2
    elif family == 1:
        # Very small random.
        n = rng.randint(2, 6)
    elif family == 2:
        # Chain: parent[i] = i-1.
        n = rng.randint(2, 14)
    elif family == 3:
        # Star: everyone's leader is the CEO.
        n = rng.randint(2, 14)
    else:
        # General random tree, parent < i guaranteed.
        n = rng.randint(2, 16)

    # Weights: positive integers, keep total modest.
    wmax = rng.choice([1, 5, 20, 100])
    w = [rng.randint(1, wmax) for _ in range(n)]

    # Build leaders respecting parent_id < child_id.
    par = [0] * n  # par[0] unused (CEO has no leader)
    for i in range(1, n):
        if family == 2:
            par[i] = i - 1
        elif family == 3:
            par[i] = 0
        else:
            par[i] = rng.randint(0, i - 1)

    out = []
    out.append(str(n))
    out.append(" ".join(str(x) for x in w))
    out.append(" ".join(str(par[i]) for i in range(1, n)))
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()
