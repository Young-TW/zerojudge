import sys
import random


def gen_url(rng):
    r = rng.random()
    if r < 0.1:
        length = 1
    elif r < 0.2:
        length = 100
    else:
        length = rng.randint(1, 100)
    chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789."
    return ''.join(rng.choice(chars) for _ in range(length))


def gen_vi(rng):
    r = rng.random()
    if r < 0.1:
        return 1
    elif r < 0.2:
        return 100
    else:
        return rng.randint(1, 100)


def main():
    rng = random.Random(int(sys.argv[1]))

    T = rng.randint(1, 5)
    print(T)

    for _ in range(T):
        for _ in range(10):
            url = gen_url(rng)
            vi = gen_vi(rng)
            print(f"{url} {vi}")


if __name__ == "__main__":
    main()
