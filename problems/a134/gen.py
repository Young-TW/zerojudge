import sys
import random


def fib_list_up_to(limit):
    """Distinct fibonacci values used by the problem: 1, 2, 3, 5, 8, 13, ..."""
    fibs = [1, 2]
    while True:
        nxt = fibs[-1] + fibs[-2]
        if nxt > limit:
            break
        fibs.append(nxt)
    return fibs


def main():
    rng = random.Random(int(sys.argv[1]))

    MAXV = 100_000_000  # values must be positive and < 100,000,000

    N = rng.randint(1, 25)
    fibs = fib_list_up_to(MAXV)

    vals = []
    for _ in range(N):
        r = rng.random()
        if r < 0.35:
            # boundary / interesting cases: smallest values and exact fib numbers
            pick = rng.random()
            if pick < 0.25:
                v = rng.randint(1, 3)                       # 1, 2, 3
            elif pick < 0.5:
                v = rng.choice(fibs)                        # exact fibonacci number
            elif pick < 0.65:
                v = rng.choice(fibs) - 1                    # one less than a fib
            elif pick < 0.8:
                v = rng.choice(fibs) + 1                    # one more than a fib
            elif pick < 0.9:
                v = MAXV - 1                                # largest allowed value
            else:
                v = MAXV - rng.randint(0, 5)                # near the upper boundary
            # keep within legal range
            if v < 1:
                v = 1
            if v > MAXV - 1:
                v = MAXV - 1
        else:
            v = rng.randint(1, MAXV - 1)
        vals.append(v)

    out = [str(N)]
    out.extend(str(v) for v in vals)
    sys.stdout.write("\n".join(out) + "\n")


main()
