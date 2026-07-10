import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep the coordinate range small so the brute-force (which loops over all
    # cells for every command) stays well under 1 second. We still cover the
    # full set of operations and all four bracket types, plus edge cases like
    # empty intervals, single points, and boundaries 0 / MAX.
    MAXV = rng.choice([5, 6, 8, 10, 15, 20])

    ops = ['U', 'I', 'D', 'C', 'S']
    brackets = ['()', '(]', '[)', '[]']

    n_commands = rng.randint(1, 40)
    lines = []
    for _ in range(n_commands):
        op = rng.choice(ops)
        br = rng.choice(brackets)

        # Bias endpoint selection toward small values and toward equality so
        # we frequently hit single-point intervals and empty open intervals.
        r = rng.random()
        if r < 0.2:
            # a == b : point or empty-open
            a = rng.randint(0, MAXV)
            b = a
        elif r < 0.35:
            # adjacent: covers single open gap
            a = rng.randint(0, max(0, MAXV - 1))
            b = a + 1
        elif r < 0.5:
            # boundary 0
            a = 0
            b = rng.randint(a, MAXV)
        elif r < 0.65:
            # boundary MAXV
            b = MAXV
            a = rng.randint(0, b)
        else:
            a = rng.randint(0, MAXV)
            b = rng.randint(a, MAXV)

        lb, rb = br[0], br[1]
        lines.append(f"{op} {lb}{a},{b}{rb}")

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == '__main__':
    main()
