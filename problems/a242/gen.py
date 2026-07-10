import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    m = rng.randint(1, 5)
    out = [str(m)]
    for _ in range(m):
        if rng.random() < 0.2:
            n = 1
        else:
            n = rng.randint(1, 8)
        out.append(str(n))
        mode = rng.randint(0, 2)
        for _ in range(n):
            if mode == 0:
                ai = 1
            elif mode == 1:
                ai = rng.randint(1, 5)
            else:
                ai = rng.randint(1, 30)
            k = rng.randint(1, 30)
            xi = ai * k
            out.append(f"{ai} {xi}")
    sys.stdout.write("\n".join(out) + "\n")


main()
