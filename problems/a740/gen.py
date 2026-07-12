import sys
import random


def gen_num(rng):
    # Cover edges and typical cases. Keep values small-ish so the brute
    # trial division (up to sqrt(n)) finishes well under 1 second.
    roll = rng.randint(0, 7)
    if roll == 0:
        return 1  # boundary: no prime factors -> sum 0
    if roll == 1:
        return 2  # smallest prime
    if roll == 2:
        # small power of two (many repeated factor 2)
        return 1 << rng.randint(1, 10)
    if roll == 3:
        # small prime itself
        return rng.choice([3, 5, 7, 11, 13, 17, 19, 23, 29, 31])
    if roll == 4:
        # product of two small primes
        ps = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
        return rng.choice(ps) * rng.choice(ps)
    if roll == 5:
        # a small range random number
        return rng.randint(1, 1000)
    if roll == 6:
        # a medium random number (brute still fast)
        return rng.randint(1, 100000)
    # larger but still fine for brute (sqrt(2*10^9) ~ 44721 iterations)
    return rng.randint(1, 2000000000)


def main():
    rng = random.Random(int(sys.argv[1]))

    # Problem input: each line one positive integer, until EOF.
    # Keep the count modest so brute stays <1s.
    t = rng.randint(1, 50)
    out = []
    for _ in range(t):
        out.append(str(gen_num(rng)))

    sys.stdout.write("\n".join(out) + "\n")


main()
