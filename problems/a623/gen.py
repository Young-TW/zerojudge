import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    r = rng.randint(0, 9)
    if r == 0:
        n, m = 0, 0
    elif r == 1:
        n = 1
        m = rng.randint(0, 1)
    elif r == 2:
        n = rng.randint(0, 20)
        m = 0
    elif r == 3:
        n = rng.randint(0, 20)
        m = n
    elif r == 4:
        n = rng.randint(0, 20)
        m = n + rng.randint(1, 3)
    elif r == 5:
        n = rng.randint(2, 20)
        m = rng.choice([1, n - 1])
    elif r == 6:
        n = rng.randint(2, 10)
        m = rng.randint(0, n)
    elif r == 7:
        n = rng.randint(10, 20)
        m = rng.randint(0, n)
    elif r == 8:
        n = 20
        m = rng.randint(0, 20)
    else:
        n = rng.randint(0, 20)
        m = rng.randint(0, n)

    sys.stdout.write("{} {}\n".format(n, m))


main()
