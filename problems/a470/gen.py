import sys
import random


def main():
    rnd = random.Random(int(sys.argv[1]))

    ncases = rnd.randint(1, 8)
    lines = [str(ncases)]

    for _ in range(ncases):
        # Pick p: mostly small so the brute finishes instantly, but
        # occasionally hit the boundaries 1 and 17.
        pchoice = rnd.randint(0, 6)
        if pchoice == 0:
            p = 1                       # lower boundary
        elif pchoice == 1:
            p = 17                      # upper boundary
        elif pchoice == 2:
            p = rnd.randint(1, 8)       # small
        elif pchoice == 3:
            p = rnd.randint(1, 17)      # full range
        else:
            p = rnd.randint(1, 10)      # medium

        # Pick q: cover boundary values and the q == p / q > p cases.
        qchoice = rnd.randint(0, 4)
        if qchoice == 0:
            q = 1                       # lower boundary
        elif qchoice == 1:
            q = 17                      # upper boundary
        elif qchoice == 2:
            q = p                       # q == p
        elif qchoice == 3:
            q = min(17, p + rnd.randint(1, 3))  # q slightly > p
        else:
            q = rnd.randint(1, 17)      # full range

        lines.append("{} {}".format(p, q))

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
