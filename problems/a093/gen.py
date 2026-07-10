import sys
import random

def main():
    rng = random.Random(int(sys.argv[1]))

    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47]
    MAX_M = 100000

    k = rng.randint(1, 6)
    chosen = sorted(rng.sample(primes, k))

    m = 1
    factors = []
    for p in chosen:
        max_e = 0
        t = m
        while t * p <= MAX_M:
            t *= p
            max_e += 1
        if max_e == 0:
            break
        e = rng.randint(1, max_e)
        m *= p ** e
        factors.append((p, e))

    if not factors:
        factors = [(2, 1)]

    print(len(factors))
    for p, e in factors:
        print(p, e)

main()
