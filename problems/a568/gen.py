import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # 1 to 4 test cases per file. N is kept small (<=3) so the brute-force
    # enumeration of every 2N-digit number finishes well within 1 second:
    #   N=1 -> 90 numbers, N=2 -> 9000, N=3 -> 900000.
    cases = rng.randint(1, 4)

    lines = []
    for _ in range(cases):
        mode = rng.randint(0, 5)
        if mode == 0:
            # lower boundary of N
            N = 1
        elif mode == 1:
            # upper boundary we allow brute to handle quickly
            N = 3
        elif mode == 2:
            # middle
            N = rng.randint(1, 3)
        elif mode == 3:
            # boundary on M: smallest allowed
            N = rng.randint(1, 3)
            M = 2
            lines.append("{} {}".format(N, M))
            continue
        elif mode == 4:
            # boundary on M: largest allowed
            N = rng.randint(1, 3)
            M = 10000
            lines.append("{} {}".format(N, M))
            continue
        else:
            # fully random within the brute-safe window
            N = rng.randint(1, 3)
        M = rng.randint(2, 10000)
        lines.append("{} {}".format(N, M))

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
