import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    lines = []
    t = rng.randint(1, 6)
    for _ in range(t):
        r = rng.randint(0, 5)
        if r == 0:
            n = 2
        elif r == 1:
            n = 10
        elif r == 2:
            n = rng.randint(2, 4)
        elif r == 3:
            n = rng.randint(5, 10)
        elif r == 4:
            n = rng.randint(2, 10)
        else:
            n = rng.randint(2, 3)

        lines.append(str(n))

        vr = rng.randint(0, 8)
        if vr == 5:
            for i in range(n):
                row = [1 if i == j else 0 for j in range(n)]
                lines.append(' '.join(map(str, row)))
        elif vr == 6:
            base = [[rng.randint(-99, 99) for _ in range(n)] for _ in range(n)]
            if n > 1:
                ri = rng.randint(0, n - 1)
                rj = rng.randint(0, n - 1)
                while rj == ri:
                    rj = rng.randint(0, n - 1)
                base[ri] = base[rj][:]
            for row in base:
                lines.append(' '.join(map(str, row)))
        elif vr == 7:
            for i in range(n):
                row = [rng.randint(-99, 99) if i == j else 0 for j in range(n)]
                lines.append(' '.join(map(str, row)))
        elif vr == 8:
            for i in range(n):
                row = [rng.randint(-99, 99) if j >= i else 0 for j in range(n)]
                lines.append(' '.join(map(str, row)))
        else:
            for i in range(n):
                if vr == 0:
                    row = [rng.randint(-99, 99) for _ in range(n)]
                elif vr == 1:
                    row = [rng.choice([-99, 99, 0, -1, 1]) for _ in range(n)]
                elif vr == 2:
                    row = [0] * n
                elif vr == 3:
                    row = [rng.randint(-3, 3) for _ in range(n)]
                elif vr == 4:
                    row = [rng.randint(-99, -50) if rng.randint(0, 1) else rng.randint(50, 99) for _ in range(n)]
                else:
                    row = [rng.randint(-1, 1) for _ in range(n)]
                lines.append(' '.join(map(str, row)))

    sys.stdout.write('\n'.join(lines) + '\n')


main()
