import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    T = rng.randint(1, 5)
    print(T)
    for _ in range(T):
        choice = rng.randint(0, 3)
        if choice == 0:
            e = rng.randint(0, 0)
            f = rng.randint(0, 0)
        elif choice == 1:
            e = rng.randint(0, 5)
            f = rng.randint(0, 5)
        elif choice == 2:
            e = rng.randint(0, 100)
            f = rng.randint(0, 100)
        else:
            e = rng.randint(0, 999)
            f = rng.randint(0, 999)
        cchoices = [2, rng.randint(2, 10), rng.randint(2, 100), rng.randint(2, 1999)]
        c = cchoices[rng.randint(0, 3)]
        print(e, f, c)


main()
