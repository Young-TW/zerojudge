import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    N = rng.randint(2, 20)

    points = set()
    order = []
    dirs = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    ox = rng.randint(-10, 10)
    oy = rng.randint(-10, 10)
    points.add((ox, oy))
    order.append((ox, oy))

    while len(order) < N:
        candidates = []
        for (px, py) in order:
            for dx, dy in dirs:
                nx, ny = px + dx, py + dy
                if (nx, ny) in points:
                    continue
                cnt = sum(1 for ddx, ddy in dirs if (nx + ddx, ny + ddy) in points)
                if cnt == 1:
                    candidates.append((nx, ny))
        if not candidates:
            break
        nx, ny = rng.choice(candidates)
        points.add((nx, ny))
        order.append((nx, ny))

    N = len(order)
    rng.shuffle(order)

    out = [str(N)]
    for (x, y) in order:
        c = rng.randint(-100, 100)
        out.append(f"{x} {y} {c}")
    print("\n".join(out))


main()
