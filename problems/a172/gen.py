import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    MAXP = 2147483647
    num_cases = rng.randint(1, 5)
    lines = []
    for _ in range(num_cases):
        r = rng.random()
        n = rng.randint(1, 20)
        if r < 0.15:
            vals = sorted(rng.sample(range(1, 1000), n))
        elif r < 0.30:
            vals = sorted(rng.sample(range(1, 1000), n), reverse=True)
        elif r < 0.40:
            v = rng.randint(1, MAXP)
            vals = [v] * n
        elif r < 0.50:
            boundary = [1, MAXP, 2, MAXP - 1]
            vals = [rng.choice(boundary) for _ in range(n)]
        else:
            vals = [rng.randint(1, MAXP) for _ in range(n)]
        lines.append(str(n))
        lines.append(" ".join(map(str, vals)))
    sys.stdout.write("\n".join(lines) + "\n")


main()
