import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    odds = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]
    n = rng.choice(odds)
    print(n)


if __name__ == "__main__":
    main()
