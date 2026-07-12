import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    r = rng.randint(0, 9)
    if r == 0:
        # boundary: smallest possible
        p = q = 1
    elif r == 1:
        # boundary: p = 1
        p = 1
        q = rng.randint(1, 100000)
    elif r == 2:
        # boundary: q = 1
        p = rng.randint(1, 100000)
        q = 1
    elif r == 3:
        # boundary: p == q
        v = rng.randint(1, 100000)
        p = q = v
    elif r == 4:
        # large values
        p = rng.randint(50000, 100000)
        q = rng.randint(50000, 100000)
    elif r == 5:
        # one much larger than the other
        if rng.random() < 0.5:
            p = rng.randint(1, 100)
            q = rng.randint(50000, 100000)
        else:
            p = rng.randint(50000, 100000)
            q = rng.randint(1, 100)
    elif r == 6:
        # small values
        p = rng.randint(1, 100)
        q = rng.randint(1, 100)
    else:
        # general case
        p = rng.randint(1, 100000)
        q = rng.randint(1, 100000)

    # The three valid coordinates derived from (p, q):
    #   min = pq,  others = p(p+q), q(p+q)
    x = p * q
    y = p * (p + q)
    z = q * (p + q)

    vals = [x, y, z]
    rng.shuffle(vals)
    print(f"{vals[0]} {vals[1]} {vals[2]}")


main()
