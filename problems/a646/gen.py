import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    n = rng.randint(1, 6)

    lines = []
    for _ in range(n):
        r = rng.random()
        if r < 0.2:
            # Boundary: small c near the low end
            c = rng.choice([1, 2, 3, 4, 5])
        elif r < 0.35:
            # Boundary: max-ish c
            c = rng.choice([998, 999])
        elif r < 0.5:
            # Mid-range
            c = rng.randint(1, 50)
        else:
            # General
            c = rng.randint(1, 999)

        rr = rng.random()
        if rr < 0.25:
            # p near 0 (very small rate -> minimal/no gain)
            p = rng.choice([0.001, 0.002, 0.005, 0.0009, 0.0001])
        elif rr < 0.45:
            # p near 1 (large gain -> lots of recycling)
            p = rng.choice([0.999, 0.998, 0.995, 0.99, 0.95])
        elif rr < 0.6:
            # Round-ish rates likely to land on integer thresholds
            p = rng.choice([0.1, 0.2, 0.25, 0.3, 0.5, 0.75, 0.333, 0.667])
        elif rr < 0.75:
            # Exactly the sample rates
            p = rng.choice([0.2, 0.3])
        else:
            # Fully random up to 3 decimals
            p = rng.randint(1, 999) / 1000.0

        lines.append("{} {}".format(c, p))

    sys.stdout.write("\n".join(lines) + "\n")


main()
