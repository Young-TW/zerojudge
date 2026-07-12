import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    t = rng.randint(1, 8)
    out = []
    for _ in range(t):
        r = rng.randint(0, 5)
        if r == 0:
            n = 1
        elif r == 1:
            n = 2
        elif r == 2:
            n = rng.randint(3, 8)
        elif r == 3:
            n = rng.randint(8, 30)
        elif r == 4:
            n = rng.randint(30, 60)
        else:
            n = rng.randint(1, 4)

        out.append(str(n))

        vr = rng.randint(0, 6)
        if vr == 0:
            vals = [rng.randint(-3, 3) for _ in range(n)]
        elif vr == 1:
            vals = [rng.randint(-1000, 1000) for _ in range(n)]
        elif vr == 2:
            vals = [rng.randint(-5, -1) for _ in range(n)]
        elif vr == 3:
            vals = [rng.randint(1, 1000) for _ in range(n)]
        elif vr == 4:
            vals = [rng.randint(-1, 1) for _ in range(n)]
        elif vr == 5:
            vals = [rng.randint(0, 0) for _ in range(n)]
        else:
            vals = []
            for _ in range(n):
                if rng.randint(0, 1) == 0:
                    vals.append(rng.randint(-1000, -100))
                else:
                    vals.append(rng.randint(100, 1000))
        out.append(' '.join(map(str, vals)))

    sys.stdout.write('\n'.join(out) + '\n0\n')


main()
