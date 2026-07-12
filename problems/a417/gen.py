import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    T = rng.randint(1, 5)
    print(T)
    for _ in range(T):
        r = rng.random()
        if r < 0.15:
            N = 1
        elif r < 0.30:
            N = 2
        else:
            N = rng.randint(1, 10)
        M = rng.randint(1, 2)
        print(N, M)


main()
