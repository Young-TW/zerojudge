import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    lines = []
    num_cases = rng.randint(1, 3)
    for _ in range(num_cases):
        n = rng.choice([1, 2, 3, 4, 5, 6, 8])
        lines.append(str(n))
        for _ in range(n):
            mode = rng.random()
            if mode < 0.3:
                forbidden = []
            elif mode < 0.5:
                forbidden = [rng.randint(1, n)]
            else:
                forbidden = [pos for pos in range(1, n + 1) if rng.random() < 0.3]
                rng.shuffle(forbidden)
            if forbidden:
                lines.append(' '.join(map(str, forbidden)) + ' 0')
            else:
                lines.append('0')
    sys.stdout.write('\n'.join(lines) + '\n')


main()
