import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Small sieve so brute stays well under 1s.
    LIMIT = 200000
    sieve = bytearray([1]) * (LIMIT + 1)
    sieve[0] = 0
    sieve[1] = 0
    for i in range(2, int(LIMIT ** 0.5) + 1):
        if sieve[i]:
            for j in range(i * i, LIMIT + 1, i):
                sieve[j] = 0
    primes = [i for i in range(2, LIMIT + 1) if sieve[i]]

    # Choose two distinct primes. Cover boundary: smallest pair, twin primes,
    # one small + one near the top, and fully random.
    r = rng.randint(0, 4)
    if r == 0:
        p = primes[0]
        q = primes[1]
    elif r == 1:
        # twin primes
        idx = rng.randint(0, len(primes) - 10)
        p = primes[idx]
        q = p + 2
        # ensure q is prime and distinct; if not, fall back
        if q >= len(sieve) or not sieve[q] or q == p:
            q = primes[idx + 1]
    elif r == 2:
        # one very small, one near the top
        p = rng.choice(primes[:5])
        q = rng.choice(primes[-50:])
        if p == q:
            q = primes[-1]
    elif r == 3:
        # both near the top
        p = rng.choice(primes[-100:])
        q = rng.choice(primes[-100:])
        while q == p:
            q = rng.choice(primes[-100:])
    else:
        p = rng.choice(primes)
        q = rng.choice(primes)
        while q == p:
            q = rng.choice(primes)

    if p > q:
        p, q = q, p

    n = p * q
    sys.stdout.write(str(n) + "\n")


main()
