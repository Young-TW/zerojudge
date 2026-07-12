import sys
from random import Random

def main():
    seed = int(sys.argv[1])
    rng = Random(seed)

    COORD = 10 ** 4  # coordinate range per problem statement

    # Two distinct system positions. Keep them distinct by retrying.
    while True:
        x1 = rng.randint(-COORD, COORD)
        y1 = rng.randint(-COORD, COORD)
        x2 = rng.randint(-COORD, COORD)
        y2 = rng.randint(-COORD, COORD)
        if (x1, y1) != (x2, y2):
            break

    # Keep n small so the brute force runs well under 1 second.
    # Occasionally exercise the minimum n = 1 case.
    if seed % 7 == 0:
        n = 1
    else:
        n = rng.randint(1, 12)

    # Distinct city coordinates. Use a set so duplicates are impossible.
    pts = set()
    while len(pts) < n:
        xi = rng.randint(-COORD, COORD)
        eta = rng.randint(-COORD, COORD)
        pts.add((xi, eta))
    pts = list(pts)

    out = []
    out.append("%d %d" % (x1, y1))
    out.append("%d %d" % (x2, y2))
    out.append("%d" % n)
    for (xi, eta) in pts:
        out.append("%d %d" % (xi, eta))
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()
