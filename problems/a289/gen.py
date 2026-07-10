#!/usr/bin/env python3
import sys
import random
from math import gcd

def main():
    rnd = random.Random(int(sys.argv[1]))
    out = []
    # 1. boundary n=1 -> any a gives b=1
    out.append((1, 1))
    # 2. n=1 with large a
    out.append((rnd.randint(2, 100000000), 1))
    # 3. a=1 -> inverse is 1
    out.append((1, rnd.randint(2, 1000)))
    # 4. n=2 with various a (parity decides existence)
    out.append((rnd.choice([1, 2, 3, 100000000]), 2))
    # 5. a = n (n>1) -> gcd = n > 1 -> No Inverse
    n5 = rnd.randint(2, 1000)
    out.append((n5, n5))
    # 6. force non-coprime: a=2, n even -> No Inverse
    out.append((2, rnd.choice([4, 6, 8, 10, 100, 1000])))
    # 7. force coprime pair
    n7 = rnd.randint(2, 1000)
    a7 = rnd.randint(1, 100000000)
    while gcd(a7, n7) != 1:
        a7 = rnd.randint(1, 100000000)
    out.append((a7, n7))
    # 8/9. random small-n pairs
    out.append((rnd.randint(1, 100000000), rnd.randint(1, 1000)))
    out.append((rnd.randint(1, 100000000), rnd.randint(1, 1000)))
    # 10. boundary a=100000000, small n
    out.append((100000000, rnd.randint(1, 1000)))
    # 11. a > n
    out.append((rnd.randint(1000, 100000000), rnd.randint(2, 1000)))
    # 12. small primes
    primes = [2, 3, 5, 7, 11, 13, 97, 997, 9973]
    out.append((rnd.choice(primes), rnd.choice(primes)))
    rnd.shuffle(out)
    for a, n in out:
        sys.stdout.write(f"{a} {n}\n")

if __name__ == "__main__":
    main()
