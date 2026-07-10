import sys, random


def main():
    rnd = random.Random(int(sys.argv[1]))
    K = rnd.randint(3, 5)
    out = [str(K)]
    for _ in range(K):
        r = rnd.random()
        if r < 0.12:
            m = 2  # smallest boundary
        elif r < 0.24:
            m = rnd.choice([3, 4, 5, 6, 7, 8, 9, 10])
        elif r < 0.40:
            # primes -> many gcd==1 cases
            m = rnd.choice([7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
                            53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
                            127, 131, 211, 307, 401, 503, 997])
        elif r < 0.55:
            m = 1 << rnd.randint(1, 12)  # powers of two up to 4096 (gcd>1 when a even)
        elif r < 0.70:
            # highly composite -> richer gcd>1 variety
            m = rnd.choice([6, 10, 12, 15, 18, 20, 24, 30, 36, 60, 100,
                            120, 210, 360, 720, 840, 2520])
        else:
            m = rnd.randint(2, 5000)

        ra = rnd.random()
        if ra < 0.10:
            a = 1  # forces c == 1
        elif ra < 0.20:
            divs = [d for d in range(2, m) if m % d == 0]
            a = rnd.choice(divs) if divs else rnd.randint(1, m - 1)
        else:
            a = rnd.randint(1, m - 1)

        b = rnd.randint(1, m - 1)
        out.append(f"{m} {a} {b}")
    print("\n".join(out))


main()
