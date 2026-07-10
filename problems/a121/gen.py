import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    mode = rng.randint(0, 8)

    if mode == 0:
        # a=1 boundary, small range
        a = 1
        b = rng.randint(1, 100)
    elif mode == 1:
        # a=b, single number, various sizes
        a = b = rng.randint(1, 100000)
    elif mode == 2:
        # a=b=1 (1 is not prime)
        a = b = 1
    elif mode == 3:
        # a=b=2 (smallest prime)
        a = b = 2
    elif mode == 4:
        # b-a = 1000 (maximum width), small a
        a = rng.randint(1, 1000)
        b = a + 1000
    elif mode == 5:
        # range starting at 1, containing 2
        a = 1
        b = rng.randint(1, 50)
    elif mode == 6:
        # near b = 1e8 (upper boundary)
        b = 100000000
        a = rng.randint(max(1, b - 1000), b)
    elif mode == 7:
        # general small case
        a = rng.randint(1, 5000)
        b = rng.randint(a, a + 1000)
    else:
        # general case, moderate size
        a = rng.randint(1, 100000)
        b = min(a + rng.randint(0, 1000), 100000000)

    print(f"{a} {b}")


if __name__ == "__main__":
    main()
