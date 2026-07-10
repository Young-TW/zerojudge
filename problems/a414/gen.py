import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    ncases = rng.randint(1, 12)
    lines = []
    for _ in range(ncases):
        mode = rng.randint(0, 5)
        if mode == 0:
            n = 1
        elif mode == 1:
            n = rng.randint(1, 3)
        elif mode == 2:
            n = rng.randint(1, 30)
        elif mode == 3:
            k = rng.randint(1, 30)
            n = (1 << k) - 1
        elif mode == 4:
            k = rng.randint(0, 30)
            n = (1 << k) - 1
            if rng.randint(0, 1) == 1:
                n = (1 << k)
            else:
                n = (1 << k) + 1
        else:
            n = rng.randint(1, 2147483647)
        lines.append(str(n))
    sys.stdout.write("\n".join(lines) + "\n0\n")


if __name__ == "__main__":
    main()
