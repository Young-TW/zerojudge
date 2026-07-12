import sys
import random

# Pool of requirement tokens; some contain spaces (like the sample's
# "vinyl roof" / "trip computer") to exercise getline-based reading.
WORDS = [
    "engine", "brakes", "tires", "ashtray", "vinyl roof", "trip computer",
    "coffee", "wheel", "mirror", "seat", "door", "window", "handle",
    "light", "horn", "battery", "exhaust", "fender", "hood", "trunk",
]

PROP_PREFIXES = ["Vendor", "Corp", "Shop", "Dealer", "Co", "Inc", "Group"]


def make_req_names(rng, n):
    # n <= 8 in all modes, pool has 20 unique entries -> always distinct.
    pool = WORDS[:]
    rng.shuffle(pool)
    return pool[:n]


def make_prop_name(rng, idx):
    return rng.choice(PROP_PREFIXES) + str(idx)


def gen_case(rng):
    mode = rng.randint(0, 6)
    lines = []

    if mode == 0:
        # boundary: smallest possible case
        n, p = 1, 1
    elif mode == 1:
        # boundary: single proposer
        n = rng.randint(1, 6)
        p = 1
    elif mode == 2:
        # boundary: every proposer meets zero requirements (r = 0)
        n = rng.randint(1, 6)
        p = rng.randint(1, 4)
    elif mode == 3:
        # tie on met count (all r = n): decided purely by price
        n = rng.randint(1, 6)
        p = rng.randint(2, 4)
    elif mode == 4:
        # full tie: identical met count AND identical price -> earliest wins
        n = rng.randint(1, 6)
        p = rng.randint(2, 4)
    elif mode == 5:
        # general small random
        n = rng.randint(1, 8)
        p = rng.randint(1, 5)
    else:
        # tiny random
        n = rng.randint(1, 4)
        p = rng.randint(1, 3)

    req = make_req_names(rng, n)
    lines.append("{0} {1}".format(n, p))
    lines.extend(req)

    if mode == 2:
        r = 0
        for i in range(p):
            d = round(rng.uniform(1.0, 100000.0), 2)
            lines.append(make_prop_name(rng, i))
            lines.append("{0:.2f} {1}".format(d, r))
    elif mode == 3:
        r = n
        for i in range(p):
            d = round(rng.uniform(1.0, 100000.0), 2)
            lines.append(make_prop_name(rng, i))
            lines.append("{0:.2f} {1}".format(d, r))
            sub = list(req)
            rng.shuffle(sub)
            lines.extend(sub)
    elif mode == 4:
        r = rng.randint(0, n)
        d = round(rng.uniform(1.0, 100000.0), 2)
        for i in range(p):
            lines.append(make_prop_name(rng, i))
            lines.append("{0:.2f} {1}".format(d, r))
            sub = rng.sample(req, r)
            lines.extend(sub)
    else:
        for i in range(p):
            r = rng.randint(0, n)
            d = round(rng.uniform(1.0, 100000.0), 2)
            lines.append(make_prop_name(rng, i))
            lines.append("{0:.2f} {1}".format(d, r))
            sub = rng.sample(req, r)
            lines.extend(sub)

    return lines


def main():
    rng = random.Random(int(sys.argv[1]))
    num_cases = rng.randint(1, 4)
    out = []
    for _ in range(num_cases):
        out.extend(gen_case(rng))
    out.append("0 0")
    sys.stdout.write("\n".join(out) + "\n")


main()
