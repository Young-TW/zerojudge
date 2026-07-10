import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    lines = []
    num_cases = rng.choice([1, 1, 1, 2])

    for _ in range(num_cases):
        # n in [2, 6]. Bias toward small n so that 5^n enumeration in the brute
        # stays trivial (6^5 = 15625 at worst, but we mostly stay small).
        r = rng.random()
        if r < 0.30:
            n = 2
        elif r < 0.60:
            n = 3
        elif r < 0.80:
            n = 4
        elif r < 0.93:
            n = 5
        else:
            n = 6

        # m in [2, 10]. Cover the boundary m=2 (tightest, fewest valid seqs)
        # and m=10 (loose; with n<=6 every shape count stays well under cap,
        # so the only active constraint is the adjacency rule).
        r = rng.random()
        if r < 0.35:
            m = 2
        elif r < 0.60:
            m = 3
        elif r < 0.80:
            m = rng.randint(4, 6)
        elif r < 0.92:
            m = 10
        else:
            m = rng.randint(2, 10)

        lines.append(f"{n} {m}")

    sys.stdout.write("\n".join(lines) + "\n")


main()
