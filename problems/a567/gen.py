import sys
import random


def gen_case(rng, out):
    # Keep N tiny so subset-enumeration brute finishes in well under 1s.
    r = rng.random()
    if r < 0.10:
        n = 1
    elif r < 0.25:
        n = rng.randint(2, 4)
    elif r < 0.80:
        n = rng.randint(5, 14)
    else:
        n = rng.randint(15, 18)

    out.append(str(n))

    mode = rng.randint(0, 7)
    for _ in range(n):
        if mode == 0:
            # very tight deadlines (all 1 or 2) -> many jobs dropped
            d = rng.randint(1, 2)
        elif mode == 1:
            # all deadline 1
            d = 1
        elif mode == 2:
            # all same deadline
            d = rng.choice([1, 2, 3, n, 10000])
        elif mode == 3:
            # deadlines equal to index-ish (barely feasible)
            d = rng.randint(1, max(1, n))
        elif mode == 4:
            # huge deadlines -> everything fits
            d = rng.randint(9000, 10000)
        elif mode == 5:
            # boundary profit values
            d = rng.randint(1, 10000)
        else:
            # general
            d = rng.randint(1, 10000)

        # profit distribution
        if mode == 5:
            p = rng.choice([1, 2, 32766, 32767 - 1])
        elif mode == 6:
            # all same profit
            p = rng.choice([1, 100, 32766])
        else:
            p = rng.randint(1, 32766)

        out.append(f"{d} {p}")


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
