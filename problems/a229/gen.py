import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    n = rng.randint(1, 10)
    print(n)


if __name__ == "__main__":
    main()
