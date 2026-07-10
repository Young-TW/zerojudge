import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    choice = rng.random()
    if choice < 0.15:
        n = 1                       # boundary: smallest
    elif choice < 0.25:
        n = 2                       # boundary
    elif choice < 0.40:
        n = rng.randint(1, 5)       # very small
    else:
        n = rng.randint(1, 20)      # small enough for brute (2^19 compositions)

    print(n)


main()
