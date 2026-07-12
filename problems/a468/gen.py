import sys
import random

MONTHS = ["January", "February", "March", "April", "May", "June",
          "July", "August", "September", "October", "November", "December"]
DAYS = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

# Problem constrains years to [2000, 2*10^9]. Keep spans small so the brute
# (which iterates year by year) finishes instantly, but exercise the leap
# rule's tricky points: div-by-400 leap (2000, 2400), div-by-100 non-leap
# (2100, 2200, 2300), Feb 29 as an endpoint, and same-day / tiny ranges.

YLO = 2000


def is_leap(y):
    return (y % 4 == 0 and y % 100 != 0) or (y % 400 == 0)


def days_in_month(y, m):
    if m == 2 and is_leap(y):
        return 29
    return DAYS[m - 1]


def random_date(rng, ylo, yhi):
    y = rng.randint(ylo, yhi)
    m = rng.randint(1, 12)
    d = rng.randint(1, days_in_month(y, m))
    return (y, m, d)


def fmt(dt):
    y, m, d = dt
    return "%s %d, %d" % (MONTHS[m - 1], d, y)


def ordered(a, b):
    return (a, b) if a <= b else (b, a)


def main():
    rng = random.Random(int(sys.argv[1]))
    r = rng.random()
    cases = []

    if r < 0.25:
        # straddle a century boundary: 2000 (leap, /400), 2100/2200/2300
        # (non-leap, /100), 2400 (leap, /400).
        centers = [2000, 2100, 2200, 2300, 2400]
        cy = rng.choice(centers)
        lo = max(YLO, cy - 4)
        hi = cy + 5
        T = rng.randint(1, 2)
        for _ in range(T):
            a = random_date(rng, lo, hi)
            b = random_date(rng, lo, hi)
            cases.append(ordered(a, b))
    elif r < 0.45:
        # Feb 29 explicitly as one endpoint (leap year guaranteed).
        y = rng.randint(2000, 2420)
        while not is_leap(y):
            y += 1
        a = (y, 2, 29)
        b = random_date(rng, y, min(y + 8, 2 * 10 ** 9))
        cases.append(ordered(a, b))
    elif r < 0.65:
        # same day, or two dates within the same year (boundary: leap day
        # before/after Feb 29 of a leap year must not be counted).
        y = rng.randint(YLO, YLO + 20)
        a = random_date(rng, y, y)
        if rng.random() < 0.5:
            b = a
        else:
            b = random_date(rng, y, y)
        cases.append(ordered(a, b))
    else:
        # general small-range cases, a few of them.
        T = rng.randint(1, 3)
        for _ in range(T):
            ylo = rng.randint(YLO, YLO + 40)
            span = rng.randint(0, 12)
            yhi = ylo + span
            a = random_date(rng, ylo, yhi)
            b = random_date(rng, ylo, yhi)
            cases.append(ordered(a, b))

    out = [str(len(cases))]
    for a, b in cases:
        out.append(fmt(a))
        out.append(fmt(b))
    sys.stdout.write("\n".join(out) + "\n")


main()
