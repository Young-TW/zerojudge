import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    t = rng.randint(1, 3)
    lines = [str(t)]

    for _ in range(t):
        mode = rng.randint(0, 6)

        if mode == 0:
            # Single circle
            n = 1
            r = rng.randint(1, 300)
            coords = [(rng.randint(-60000, 60000), rng.randint(-60000, 60000))]

        elif mode == 1:
            # All circles at the same point -> 1 component
            n = rng.randint(2, 10)
            r = rng.randint(1, 300)
            cx = rng.randint(-60000, 60000)
            cy = rng.randint(-60000, 60000)
            coords = [(cx, cy) for _ in range(n)]

        elif mode == 2:
            # Tangent chain: centers exactly 2R apart (boundary: d == 2R)
            n = rng.randint(2, 8)
            r = rng.randint(1, 300)
            step = 2 * r
            sx = rng.randint(-10000, 10000)
            sy = rng.randint(-10000, 10000)
            coords = [(sx + i * step, sy) for i in range(n)]

        elif mode == 3:
            # Just barely separate: 2R+1 apart (d > 2R)
            n = rng.randint(2, 8)
            r = rng.randint(1, 300)
            step = 2 * r + 1
            sx = rng.randint(-10000, 10000)
            sy = rng.randint(-10000, 10000)
            coords = [(sx + i * step, sy) for i in range(n)]

        elif mode == 4:
            # Boundary coordinate values mixed with random
            n = rng.randint(1, 30)
            r = rng.choice([1, 2, 100, 300, rng.randint(1, 300)])
            edge_vals = [-60000, -1, 0, 1, 60000]
            coords = []
            for _ in range(n):
                if rng.random() < 0.4:
                    x = rng.choice(edge_vals)
                else:
                    x = rng.randint(-60000, 60000)
                if rng.random() < 0.4:
                    y = rng.choice(edge_vals)
                else:
                    y = rng.randint(-60000, 60000)
                coords.append((x, y))

        elif mode == 5:
            # Clustered circles in a small area -> likely 1 component
            n = rng.randint(4, 20)
            r = rng.randint(50, 300)
            coords = [(rng.randint(-500, 500), rng.randint(-500, 500))
                      for _ in range(n)]

        else:
            # Fully random
            n = rng.randint(1, 40)
            r = rng.randint(1, 300)
            coords = [(rng.randint(-60000, 60000), rng.randint(-60000, 60000))
                      for _ in range(n)]

        lines.append("%d %d" % (n, r))
        for x, y in coords:
            lines.append("%d %d" % (x, y))

    print("\n".join(lines))


main()
