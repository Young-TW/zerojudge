import sys
import random


def gen_case(rng, out):
    # Keep N tiny so 2^N brute finishes in well under 1s.
    r = rng.random()
    if r < 0.10:
        n = 1
    elif r < 0.25:
        n = rng.randint(2, 6)
    elif r < 0.85:
        n = rng.randint(7, 16)
    else:
        n = rng.randint(17, 20)

    out.append(str(n))

    mode = rng.randint(0, 8)
    for _ in range(n):
        if mode == 0:
            # strictly increasing -> whole array qualifies
            v = rng.randint(1, 100)
        elif mode == 1:
            # all equal -> only one element can be picked
            v = rng.choice([1, 5, 1000000])
        elif mode == 2:
            # strictly decreasing -> best is single max
            v = rng.randint(1, 100)
        elif mode == 3:
            # boundary value 1 (smallest)
            v = 1
        elif mode == 4:
            # boundary value 1,000,000 (largest)
            v = 1000000
        elif mode == 5:
            # small pool, lots of duplicates
            v = rng.choice([1, 2, 3, 7])
        elif mode == 6:
            # few distinct values
            v = rng.randint(1, 5)
        elif mode == 7:
            # general
            v = rng.randint(1, 1000000)
        else:
            # wide range
            v = rng.randint(1, 1000)
        out.append(str(v))


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    out = []
    # Emit 1-4 test cases to exercise the multi-testcase loop.
    ncases = rng.randint(1, 4)
    for _ in range(ncases):
        gen_case(rng, out)
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
