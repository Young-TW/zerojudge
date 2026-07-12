import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    n = rng.randint(1, 20)

    max_x = rng.choice([2, 3, 5, 10, 20, 50, 100, 1000, 1000000])
    if max_x < n:
        max_x = n

    # Generate strictly increasing Xi
    seen = set()
    xis = []
    while len(xis) < n:
        x = rng.randint(0, max_x)
        if x not in seen:
            seen.add(x)
            xis.append(x)
    xis.sort()

    speed_mode = rng.randint(0, 4)
    lines = [str(n)]
    for i in range(n):
        if speed_mode == 0:
            # All same speed (no overtakes)
            v = 1
        elif speed_mode == 1:
            # Strictly decreasing speeds (max overtakes, may be simultaneous)
            v = max(1, 100 - i)
        elif speed_mode == 2:
            # Strictly increasing speeds (no overtakes)
            v = min(100, i + 1)
        elif speed_mode == 3:
            # All max speed
            v = 100
        else:
            # Random speeds
            v = rng.randint(1, 100)
        lines.append("{} {}".format(xis[i], v))

    sys.stdout.write("\n".join(lines) + "\n")


main()
