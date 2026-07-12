import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Scale deliberately small so brute force runs well under 1 second,
    # but large enough to cover various cases including boundaries.
    n = rng.randint(1, 200)

    lines = [str(n)]

    # Boundary-targeting value sets for m so that exact thresholds are hit.
    # x >= 10.00%  <=>  p >= m * 110 / 100  (i.e. p >= m + m/10, needs 10 | m)
    # x <= -7.00%  <=>  p <= m * 93  / 100  (i.e. p <= m - 7m/100, needs 100 | 7m)
    # We pick m values that are multiples of 100 so both thresholds land on integers.
    boundary_ms = [100, 200, 1000, 10000, 100000]

    for _ in range(n):
        r = rng.random()
        if r < 0.35:
            # Boundary cases: choose m from boundary_ms, then p at/near exact thresholds
            m = rng.choice(boundary_ms)
            lo = 1
            hi = 100000
            # clamp p to valid range [1, 100000]
            p_exact_10 = m + m // 10        # exactly +10.00%
            p_exact_neg7 = m - (7 * m) // 100  # exactly -7.00%
            choices = []
            for pc in [p_exact_10, p_exact_10 - 1, p_exact_10 + 1,
                       p_exact_neg7, p_exact_neg7 - 1, p_exact_neg7 + 1,
                       m, m + 1, m - 1]:
                if 1 <= pc <= 100000:
                    choices.append(pc)
            p = rng.choice(choices) if choices else rng.randint(lo, hi)
        elif r < 0.55:
            # Extremes and edge values
            m = rng.choice([1, 1, 2, 3, 99999, 100000, 100000])
            p = rng.choice([1, 2, 100000, 99999, m, m + 1, m - 1 if m > 1 else 1,
                            rng.randint(1, 100000)])
            p = max(1, min(100000, p))
        else:
            # Fully random within the full allowed range
            m = rng.randint(1, 100000)
            p = rng.randint(1, 100000)

        lines.append("{} {}".format(m, p))

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
