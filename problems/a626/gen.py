import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Multiple test cases per file (problem reads until EOF).
    t = rng.randint(1, 6)
    out = []
    for _ in range(t):
        r = rng.randint(0, 8)
        if r == 0:
            # boundary: smallest valid input
            n = 1
        elif r == 1:
            # boundary: just below first prime
            n = 2
        elif r == 2:
            # small values
            n = rng.randint(2, 10)
        elif r == 3:
            # value near first prime cluster
            n = rng.randint(10, 50)
        elif r == 4:
            # upper bound
            n = 1000
        elif r == 5:
            # one below upper bound
            n = 999
        elif r == 6:
            # medium values
            n = rng.randint(100, 500)
        elif r == 7:
            # prime-looking N itself
            n = rng.choice([2, 3, 5, 7, 11, 13, 97, 997])
        else:
            # general case
            n = rng.randint(1, 1000)
        out.append(str(n))
    sys.stdout.write('\n'.join(out) + '\n')


main()
