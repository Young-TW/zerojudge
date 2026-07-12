#!/usr/bin/env python3
import sys
from random import Random

def rnd_digits(rng, lo, hi):
    n = rng.randint(lo, hi)
    if n <= 0:
        return "0"
    s = str(rng.randint(1, 9))
    for _ in range(n - 1):
        s += str(rng.randint(0, 9))
    return s

def rand_num(rng, min_d, max_d, allow_lead=True):
    n = rng.randint(min_d, max_d)
    if n <= 0:
        return "0"
    if n == 1:
        return str(rng.randint(0, 9))
    first = rng.randint(1, 9) if not allow_lead else rng.randint(0, 9)
    s = str(first)
    for _ in range(n - 1):
        s += str(rng.randint(0, 9))
    return s

def make_dividend(rng, divisor, q_digits):
    q = rnd_digits(rng, q_digits, q_digits)
    r = rand_num(rng, 1, max(1, len(divisor)), allow_lead=False) if int(divisor) > 1 else "0"
    if r == "0" or len(r) >= len(divisor):
        if len(divisor) == 1:
            r = str(rng.randint(0, int(divisor)-1))
        else:
            r = str(rng.randint(1, 9))
            for _ in range(len(divisor) - 2):
                r += str(rng.randint(0, 9))
    # dividend = divisor * q + r  via Python big ints
    d = str(int(divisor) * int(q) + int(r))
    return d

def main():
    seed = int(sys.argv[1])
    rng = Random(seed)

    cases = []
    # boundaries
    cases.append(("0", "1"))              # dividend 0
    cases.append(("5", "6"))              # q=0, sample
    cases.append(("6", "6"))              # exact
    cases.append(("7", "1"))              # divisor 1
    cases.append(("100000000000", "1"))   # divisor 1, big dividend
    cases.append(("9", "9"))              # equal
    cases.append(("999999", "100000"))    # q=9, r=99999
    cases.append(("100000", "999999"))    # q=0

    # divisor = 1, various sizes
    cases.append((rnd_digits(rng, 3, 8), "1"))

    # exact multiples
    for _ in range(3):
        b = rnd_digits(rng, 1, 4)
        q = rnd_digits(rng, 1, 4)
        d = str(int(b) * int(q))
        cases.append((d, b))

    # random with bounded quotient (repeated-subtraction friendly)
    for _ in range(8):
        b = rnd_digits(rng, 1, 6)
        if int(b) == 0:
            b = "1"
        qd = rng.randint(1, 3)
        d = make_dividend(rng, b, qd)
        cases.append((d, b))

    # larger dividend, divisor small so quotient fits ~3-4 digits
    for _ in range(2):
        b = str(rng.randint(1, 9))
        d = make_dividend(rng, b, 4)
        cases.append((d, b))

    # leading zeros injected (still legal digits)
    for _ in range(2):
        b = rnd_digits(rng, 1, 3)
        d = make_dividend(rng, b, 2)
        d = "0" * rng.randint(1, 4) + d
        b = "0" * rng.randint(1, 3) + b
        cases.append((d, b))

    # a couple of fully random larger (but still small)
    for _ in range(2):
        d = rnd_digits(rng, 6, 12)
        b = rnd_digits(rng, 1, 6)
        if int(b) == 0:
            b = "1"
        cases.append((d, b))

    for i, (a, bb) in enumerate(cases):
        sys.stdout.write(a + " " + bb + ("\n" if i < len(cases)-1 else ""))

if __name__ == "__main__":
    main()
