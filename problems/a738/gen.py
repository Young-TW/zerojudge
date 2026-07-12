import sys
import random


def gen_pair(rng):
    # Problem constraint: 0 < a, b < 1e9. Keep small so brute runs <1s,
    # but cover boundaries: min value (1), near-max value, and small/mid
    # ranges so the brute's trial-division approach is fast.
    roll = rng.randint(0, 5)
    if roll == 0:
        # Both at minimum boundary.
        a = 1
        b = 1
    elif roll == 1:
        # One near max boundary.
        a = rng.randint(1, 10)
        b = 1000000000 - rng.randint(0, 9)
    elif roll == 2:
        # Very small numbers (brute-friendly, many GCD steps covered).
        a = rng.randint(1, 100)
        b = rng.randint(1, 100)
    elif roll == 3:
        # One divides the other (gcd = the smaller).
        a = rng.randint(1, 10000)
        b = a * rng.randint(1, 1000)
        if b >= 1000000000:
            b = 1000000000 - 1
    elif roll == 4:
        # Coprime-ish random mid-size pair.
        a = rng.randint(1, 100000)
        b = rng.randint(1, 100000)
    else:
        # General random within full small-ish range (brute still fast).
        a = rng.randint(1, 1000000)
        b = rng.randint(1, 1000000)
    # Guarantee strict bounds 0 < a, b < 1e9.
    if a < 1:
        a = 1
    if b < 1:
        b = 1
    if a > 999999999:
        a = 999999999
    if b > 999999999:
        b = 999999999
    return a, b


def main():
    rng = random.Random(int(sys.argv[1]))

    # Input is line-based, EOF-terminated (no test count). Keep the number
    # of pairs small so brute runs well under 1 second.
    n = rng.randint(1, 20)
    out = []
    for _ in range(n):
        a, b = gen_pair(rng)
        out.append(str(a) + " " + str(b))

    sys.stdout.write("\n".join(out) + "\n")


main()
