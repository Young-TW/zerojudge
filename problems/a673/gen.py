import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Number of test cases per run. Keep small for brute-force enumeration.
    T = rng.randint(1, 3)

    lines = []
    lines.append(str(T))

    for _ in range(T):
        # small N so N! enumeration finishes well under 1s (<=8)
        # but cover boundary N=1
        r = rng.randint(0, 5)
        if r == 0:
            N = 1
        elif r == 1:
            N = 2
        elif r == 2:
            N = rng.randint(3, 5)
        elif r == 3:
            N = rng.randint(6, 8)
        elif r == 4:
            N = rng.randint(6, 8)
        else:
            N = rng.randint(1, 8)

        lines.append("")  # blank line before each case (also after first line)
        lines.append(str(N))

        for _ in range(N):
            if rng.randint(0, 2) == 0:
                # boundary value cases
                t = rng.choice([1, 1, 1000, 1000])
                f = rng.choice([1, 1, 1000, 1000])
            else:
                t = rng.randint(1, 1000)
                f = rng.randint(1, 1000)
            lines.append("{} {}".format(t, f))

    sys.stdout.write("\n".join(lines) + "\n")


main()
