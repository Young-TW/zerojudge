import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    small_prime_sq = [4, 9, 25, 49, 121, 169, 289, 361, 529, 841, 961]
    large_prime_sq = [997 * 997, 991 * 991, 983 * 983, 977 * 977, 971 * 971]
    composite_sq = [16, 36, 64, 100, 144, 256, 400, 576, 625, 784, 900, 1024]
    primes = [2, 3, 5, 7, 11, 13, 97, 101, 991, 997]
    semiprime = [6, 10, 14, 15, 21, 22, 26, 33, 35, 9797]
    cubes = [8, 27, 125, 343]
    misc = [1, 12, 18, 24, 30, 48, 72, 120, 1000, 999983]

    boundaries = (small_prime_sq + large_prime_sq + composite_sq +
                  primes + semiprime + cubes + misc)

    if seed % 7 == 0:
        n = 1
    else:
        n = rng.randint(1, 20)

    vals = []
    for _ in range(n):
        r = rng.random()
        if r < 0.5:
            v = rng.choice(boundaries)
        elif r < 0.8:
            v = rng.randint(1, 1000)
        else:
            v = rng.randint(1, 1000000)
        vals.append(str(v))

    sys.stdout.write(str(n) + "\n")
    sys.stdout.write(" ".join(vals) + "\n")


if __name__ == "__main__":
    main()
