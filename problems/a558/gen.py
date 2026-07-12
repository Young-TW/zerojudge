import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep n small so the brute-force (which runs a bitmask DP over the
    # odd-degree vertices, of which there are 2^n when n is odd) stays
    # well under 1 second.  n == 4 (odd) gives 16 odd vertices ->
    # 2^16 DP states, already near the comfort limit, so cap odd-n
    # cases at 4.  Even-n cases have no odd vertices, so they are cheap;
    # allow up to 8 to exercise a bigger graph on the cheap path.
    t = rng.randint(1, 6)
    out = ["{}".format(t)]
    for _ in range(t):
        r = rng.randint(0, 5)
        if r == 0:
            n = 2                      # boundary: minimum n
        elif r == 1:
            n = 3                      # small odd
        elif r == 2:
            n = rng.choice([4, 4, 5])  # 4 odd (16 odd verts DP), 5 odd(32 -> skip)
        elif r == 3:
            n = rng.randint(2, 4)
        elif r == 4:
            n = rng.choice([2, 3, 4])  # mix
        else:
            n = rng.choice([2, 3, 4, 6, 8])  # even-n larger graphs are cheap

        # If we landed on an odd n that is too big for the brute DP,
        # clamp it back down to 4.  (odd and <= 4)
        if n % 2 == 1 and n > 4:
            n = 4

        # c: cover boundaries 1 and 100, plus random middle values.
        cr = rng.randint(0, 3)
        if cr == 0:
            c = 1                      # boundary: minimum c
        elif cr == 1:
            c = 100                    # boundary: maximum c
        elif cr == 2:
            c = rng.randint(1, 100)
        else:
            c = rng.randint(1, 10)

        out.append("{} {}".format(n, c))

    sys.stdout.write("\n".join(out) + "\n")


main()
