import sys
import random


def gen_case(rng, out):
    # Keep N tiny so 2^N subset-enumeration brute finishes in well under 1s.
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

    mode = rng.randint(0, 8)
    for _ in range(n):
        # value distribution
        if mode == 5:
            v = rng.choice([1, 2, 99999, 100000])
        elif mode == 6:
            v = rng.choice([1, 100, 100000])
        else:
            v = rng.randint(1, 100000)

        # interval distribution
        if mode == 0:
            # tiny range -> heavy overlap
            s = rng.randint(1, 5)
            e = rng.randint(s + 1, 6)
        elif mode == 1:
            # all start at 1
            s = 1
            e = rng.randint(2, 1000000)
        elif mode == 2:
            # all same interval
            base_s = rng.randint(1, 1000000)
            base_e = rng.randint(base_s + 1, 1000000)
            s = base_s
            e = base_e
        elif mode == 3:
            # adjacent-ish intervals
            s = rng.randint(1, 100)
            e = rng.randint(s + 1, s + 3)
        elif mode == 4:
            # wide spread -> little overlap
            s = rng.randint(1, 1000000)
            e = rng.randint(min(s + 1, 1000000), min(s + 2, 1000000))
        elif mode == 7:
            # boundary time values
            s = rng.choice([1, 1, 999999])
            e = rng.randint(min(s + 1, 1000000), 1000000)
        else:
            # general
            s = rng.randint(1, 1000000)
            e = rng.randint(s + 1, 1000000)

        out.append(f"{s} {e} {v}")


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
