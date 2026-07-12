import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    cases = []

    # ---- Edge / boundary cases (kept tiny so brute runs in well under 1s) ----

    # 1) n == 0 must always be YES (empty subset).
    #    p at its minimum 1.
    cases.append((0, 1, [13]))

    # 2) n == 0 with several bars (still YES via empty subset).
    cases.append((0, 3, [5, 7, 9]))

    # 3) p at its maximum 20, small bar lengths so brute (2^20) is fast.
    #    n exactly reachable as a single bar.
    bars20 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
              11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    cases.append((7, 20, bars20[:]))            # single bar 7 -> YES
    cases.append((55, 20, bars20[:]))           # sum 1..10 = 55 -> YES
    cases.append((210, 20, bars20[:]))          # sum of all = 210 -> YES
    cases.append((211, 20, bars20[:]))          # one over total -> NO
    cases.append((1, 20, bars20[:]))            # smallest bar -> YES

    # 4) n larger than sum of all bars -> NO.
    cases.append((1000, 3, [1, 2, 3]))

    # 5) n exactly equal to the only bar -> YES.
    cases.append((42, 1, [42]))

    # 6) n one less than the only bar -> NO.
    cases.append((41, 1, [42]))

    # 7) The provided sample cases (so the generator stays consistent with spec).
    cases.append((25, 4, [10, 12, 5, 7]))       # NO
    cases.append((925, 10, [45, 15, 120, 500, 235, 58, 6, 12, 175, 70]))  # YES
    cases.append((120, 5, [25, 25, 25, 25, 25]))  # NO (5*25=125 != 120)
    cases.append((0, 2, [13, 567]))             # YES (empty subset)

    # 8) Duplicate bars forming exactly n.
    cases.append((50, 5, [25, 25, 25, 25, 25]))  # YES (two 25s)
    cases.append((100, 4, [25, 25, 25, 25]))     # YES (four 25s)
    cases.append((75, 4, [25, 25, 25, 25]))      # YES (three 25s)
    cases.append((99, 4, [25, 25, 25, 25]))      # NO

    # 9) Single bar equal to n when n is at the max boundary.
    cases.append((1000, 1, [1000]))              # YES
    cases.append((999, 1, [1000]))               # NO

    # ---- Small random cases, kept small for brute speed ----
    # p <= 15 -> 2^15 = 32768, trivially fast even in bulk.

    for _ in range(22):
        p = rng.randint(1, 15)                   # 2^15 = 32768, very fast
        bars = [rng.randint(1, 100) for _ in range(p)]
        # bias n toward reachable & just-out-of-reach values
        s = sum(bars)
        r = rng.random()
        if r < 0.4:
            n = rng.randint(0, s)                # often reachable
        elif r < 0.7:
            n = s                                 # total -> YES
        else:
            n = rng.randint(0, 1000)             # arbitrary
        cases.append((n, p, bars))

    # A couple of cases with p = 20 but tiny bar lengths (1 or 2) to exercise
    # the full 2^20 sweep while staying well under a second.
    for _ in range(2):
        bars = [rng.choice([1, 2]) for _ in range(20)]
        n = rng.randint(0, 40)
        cases.append((n, 20, bars))

    # ---- Emit ----
    out = []
    out.append(str(len(cases)))
    for n, p, bars in cases:
        out.append(str(n))
        out.append(str(p))
        out.append(" ".join(str(b) for b in bars))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
