import sys
import random


def gen_num(rng):
    # Cover edges and typical cases. Values stay within the problem's
    # 64-bit bound (<= 999999999999999). Brute is O(digits) so even the
    # max value is trivially fast; we keep the case count modest.
    roll = rng.randint(0, 10)
    if roll == 0:
        return 0  # boundary: zero -> "0"
    if roll == 1:
        return 1  # smallest positive
    if roll == 2:
        # exact unit boundaries
        return rng.choice([100, 1000, 100000, 10000000])
    if roll == 3:
        # one less than a unit boundary
        return rng.choice([99, 999, 99999, 9999999])
    if roll == 4:
        # sample-like small number
        return rng.randint(1, 100000)
    if roll == 5:
        # medium number spanning several units
        return rng.randint(1, 100000000)
    if roll == 6:
        # forces a kuti split with a non-trivial upper part
        return rng.randint(10000000, 999999999999999)
    if roll == 7:
        # multiple kuti groups (>= 10^14) to exercise recursion
        return rng.randint(100000000000000, 999999999999999)
    if roll == 8:
        # pure kuti boundary: exactly 10^7 -> "1 kuti"
        return 10000000
    if roll == 9:
        # 10^14 -> "1 kuti kuti" (recursion produces bare "kuti")
        return 100000000000000
    # large random within full bound
    return rng.randint(0, 999999999999999)


def main():
    rng = random.Random(int(sys.argv[1]))

    # Problem input: each line one non-negative integer, until EOF.
    # Keep the count modest so brute stays <1s.
    t = rng.randint(1, 50)
    out = []
    for _ in range(t):
        out.append(str(gen_num(rng)))

    sys.stdout.write("\n".join(out) + "\n")


main()
