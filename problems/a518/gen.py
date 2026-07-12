import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Boundary / tricky pairs for a 100-channel circular TV (0..99).
    # Covers: same channel, adjacent, wrap-around, antipodal, extremes.
    edge_cases = [
        (0, 0),       # same channel -> 0
        (3, 3),       # same channel mid-range -> 0
        (99, 99),     # same channel at edge -> 0
        (3, 9),       # sample: -> 6
        (0, 99),      # sample: wrap up -> 1
        (99, 0),      # wrap down -> 1
        (0, 1),       # adjacent at low edge -> 1
        (98, 99),     # adjacent at high edge -> 1
        (12, 27),     # sample: -> 15
        (0, 50),      # antipodal -> 50
        (50, 0),      # antipodal reversed -> 50
        (49, 50),     # adjacent across midpoint -> 1
        (50, 49),     # adjacent across midpoint reversed -> 1
        (0, 49),      # 49 up vs 51 down -> 49
        (0, 51),      # 51 up vs 49 down -> 49
        (1, 99),      # 2 up (wrap) vs 98 down -> 2
        (99, 1),      # 2 down (wrap) vs 98 up -> 2
        (2, 97),      # 5 up (wrap) vs 95 down -> 5
        (97, 2),      # 5 down (wrap) vs 95 up -> 5
    ]

    cases = list(edge_cases)

    # A handful of small random cases across the full channel range.
    for _ in range(12):
        a = rng.randint(0, 99)
        b = rng.randint(0, 99)
        cases.append((a, b))

    # Sometimes include the exact max-case count to exercise the loop limit.
    # Still tiny (<=200 lines) so brute runs instantly.
    while len(cases) < 200:
        a = rng.randint(0, 99)
        b = rng.randint(0, 99)
        cases.append((a, b))
    cases = cases[:200]

    out = []
    for a, b in cases:
        out.append("%d %d" % (a, b))
    out.append("-1 -1")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
