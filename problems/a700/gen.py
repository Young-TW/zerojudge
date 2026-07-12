import sys
import random


def main():
    rnd = random.Random(int(sys.argv[1]))
    n = rnd.randint(1, 30)
    out = []
    for _ in range(n):
        if rnd.random() < 0.3:
            i = rnd.choice([1, 7])
            j = rnd.choice([1, 8])
        else:
            i = rnd.randint(1, 7)
            j = rnd.randint(1, 8)
        out.append("%d %d" % (i, j))
    sys.stdout.write("\n".join(out) + "\n")


main()
