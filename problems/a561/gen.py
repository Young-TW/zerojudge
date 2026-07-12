import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep n small so brute force (std::sort) runs in well under 1
    # second, but large enough to exercise the "index % 10 == 0"
    # output path multiple times.  Values are distinct non-negative
    # integers < 10^7 (problem constraint), and we deliberately cover
    # boundary sizes and value ranges.

    r = rng.randint(0, 9)
    if r == 0:
        n = 1                       # boundary: minimum n
    elif r == 1:
        n = 10                      # boundary: exactly one output value
    elif r == 2:
        n = 11                      # boundary: just past one output value
    elif r == 3:
        n = 20                      # boundary: two output values
    elif r == 4:
        n = rng.randint(0, 0)       # boundary: n == 0 (empty)
        n = 0
    elif r == 5:
        n = rng.randint(1, 5)       # small random
    elif r == 6:
        n = rng.randint(10, 30)     # ensures multiple %10 outputs
    elif r == 7:
        n = rng.randint(50, 200)    # a bit larger, still instant
    elif r == 8:
        n = rng.choice([9, 19, 29, 99])  # just-below-multiple edges
    else:
        n = rng.randint(200, 1000)  # stress-ish but still < 1s for brute

    # Value-range variants.  All values must be distinct, non-negative,
    # and < 10^7.
    vr = rng.randint(0, 6)
    universe = 10000000
    if vr == 0:
        # small dense values starting at 0
        vals = list(range(n))
        rng.shuffle(vals)
    elif vr == 1:
        # values including 0 (boundary value)
        pool = list(range(0, min(universe, 2 * n + 5)))
        rng.shuffle(pool)
        vals = pool[:n]
    elif vr == 2:
        # values near the top of the allowed range
        pool = list(range(universe - 2 * n - 5, universe))
        rng.shuffle(pool)
        vals = pool[:n]
    elif vr == 3:
        # mix of 0 and near-max
        cand = [0, universe - 1] + [rng.randint(0, universe - 1)
                                    for _ in range(2 * n + 5)]
        seen = set()
        vals = []
        for x in cand:
            if x not in seen:
                seen.add(x)
                vals.append(x)
            if len(vals) == n:
                break
        rng.shuffle(vals)
    elif vr == 4:
        # already sorted ascending
        pool = list(range(0, min(universe, 2 * n + 5)))
        rng.shuffle(pool)
        vals = sorted(pool[:n])
    elif vr == 5:
        # already sorted descending (worst case for many sorts)
        pool = list(range(0, min(universe, 2 * n + 5)))
        rng.shuffle(pool)
        vals = sorted(pool[:n], reverse=True)
    else:
        # fully random distinct values across the whole range
        pool = rng.sample(range(universe), n)
        vals = pool

    # Make sure we have exactly n distinct values (guard against the
    # rare case where a variant produced fewer, e.g. n==0).
    if len(vals) < n:
        extra = rng.sample(range(universe), n - len(vals))
        s = set(vals)
        for x in extra:
            if x not in s:
                vals.append(x)
                s.add(x)

    out = [str(n)]
    if n > 0:
        out.append(" ".join(str(v) for v in vals))
    sys.stdout.write("\n".join(out) + "\n")


main()
