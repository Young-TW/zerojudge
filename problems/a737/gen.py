import sys
import random


def gen_case(rng):
    # Keep small so brute runs <1s. Cover edges: r=1, small, mid, and
    # a "many duplicates / clustered" case. Door numbers 0<si<30000.
    roll = rng.randint(0, 4)
    if roll == 0:
        r = 1  # boundary: single relative -> min distance is 0
    elif roll == 1:
        r = rng.randint(2, 8)  # tiny
    elif roll == 2:
        r = rng.randint(20, 60)  # small
    elif roll == 3:
        r = rng.randint(100, 300)  # still well under 1s for brute
    else:
        # Force many collisions / clustered values on a tiny pool.
        r = rng.randint(50, 200)

    nums = []
    for _ in range(r):
        if roll == 4:
            # Bias toward a tiny pool so duplicates/clustered values are likely.
            base = rng.choice([1, 2, 3, 9999, 29999, 15000])
            v = base + rng.randint(-3, 3)
            if v < 1:
                v = 1
            if v > 29999:
                v = 29999
            nums.append(str(v))
        else:
            hi = rng.randint(0, 9)
            if hi == 0:
                v = 1  # min boundary
            elif hi == 1:
                v = 29999  # max boundary
            else:
                v = rng.randint(1, 29999)
            nums.append(str(v))

    return str(r) + " " + " ".join(nums)


def main():
    rng = random.Random(int(sys.argv[1]))

    # Problem input format: first line = number of test cases t.
    # Keep t small so total brute work stays <1s.
    t = rng.randint(1, 5)
    out = [str(t)]
    for _ in range(t):
        out.append(gen_case(rng))

    sys.stdout.write("\n".join(out) + "\n")


main()
