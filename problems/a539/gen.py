import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    t = rng.randint(1, 5)
    out = []
    for _ in range(t):
        r = rng.randint(0, 5)
        if r == 0:
            n = 0
        elif r == 1:
            n = 1
        elif r == 2:
            n = 2
        elif r == 3:
            n = rng.randint(3, 8)
        elif r == 4:
            n = rng.randint(8, 30)
        else:
            n = rng.randint(30, 100)

        out.append(str(n))

        if n > 0:
            vr = rng.randint(0, 4)
            if vr == 0:
                vals = [rng.randint(-3, 3) for _ in range(n)]
            elif vr == 1:
                vals = sorted(rng.randint(-1000, 1000) for _ in range(n))
            elif vr == 2:
                vals = sorted((rng.randint(-1000, 1000) for _ in range(n)), reverse=True)
            elif vr == 3:
                vals = [rng.randint(0, 0) for _ in range(n)]
            else:
                vals = [rng.randint(-1000, 1000) for _ in range(n)]
            out.append(' '.join(map(str, vals)))

    sys.stdout.write('\n'.join(out) + '\n')


main()
