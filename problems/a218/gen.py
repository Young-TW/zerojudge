import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    lines = []
    num_cases = rng.randint(1, 3)
    for _ in range(num_cases):
        n = rng.choice([1, 2, 5, 10, 20])
        vals = [rng.randint(0, 9) for _ in range(n)]
        rng.shuffle(vals)
        lines.append(str(n))
        lines.append(' '.join(map(str, vals)))
    sys.stdout.write('\n'.join(lines) + '\n')


main()
