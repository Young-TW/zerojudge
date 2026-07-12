import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # One test file per invocation: a handful of lines (<= 10000 limit trivially).
    # Keep values small so O(n) brute per query runs well under 1s.
    k = rng.randint(1, 20)

    lines = []
    for _ in range(k):
        roll = rng.randint(0, 6)
        if roll == 0:
            v = 0  # lower boundary
        elif roll == 1:
            v = 1  # unit (not prime)
        elif roll == 2:
            v = 2  # smallest prime
        elif roll == 3:
            v = rng.choice([3, 5, 7, 11, 13, 17, 19, 23, 29, 31])  # small primes
        elif roll == 4:
            v = rng.choice([4, 6, 8, 9, 10, 12, 15, 21, 25, 27, 49])  # small composites
        elif roll == 5:
            v = rng.randint(0, 2000)  # general small range
        else:
            # a few larger values but still tiny for brute (<=2000 keeps O(n) fast)
            v = rng.randint(0, 2000)
        lines.append(str(v))

    sys.stdout.write("\n".join(lines) + "\n")


main()
