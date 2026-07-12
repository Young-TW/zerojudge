import sys
import random


def gen_case(rng, out):
    # Pick a small scenario that exercises edges but keeps brute fast (<1s).
    r = rng.random()
    if r < 0.10:
        n = 1
    elif r < 0.25:
        n = rng.randint(2, 4)
    elif r < 0.70:
        n = rng.randint(5, 30)
    else:
        n = rng.randint(31, 60)

    # Height distribution mode.
    mode = rng.randint(0, 6)
    h = []
    for i in range(n):
        if mode == 0:
            # tiny heights -> many coincidences (width-1 queries match a lot)
            h.append(rng.randint(1, 3))
        elif mode == 1:
            # all equal
            v = rng.randint(1, 1000000000)
            h.append(v)
        elif mode == 2:
            # only two distinct values, alternating-ish
            a = rng.randint(1, 5)
            b = rng.randint(1, 5)
            h.append(a if rng.random() < 0.5 else b)
        elif mode == 3:
            # small with repeats
            h.append(rng.randint(1, 8))
        elif mode == 4:
            # full range up to 1e9 (few collisions)
            h.append(rng.randint(1, 1000000000))
        elif mode == 5:
            # palindrome-like (h[i] + h[n+1-i] constant -> many matches)
            half = [rng.randint(1, 5) for _ in range(n // 2)]
            if n % 2 == 0:
                h = half + half[::-1]
            else:
                h = half + [rng.randint(1, 5)] + half[::-1]
        else:
            # near-palindrome with noise
            half = [rng.randint(1, 5) for _ in range(n // 2)]
            if n % 2 == 0:
                h = half + half[::-1]
            else:
                h = half + [rng.randint(1, 5)] + half[::-1]
            for _ in range(rng.randint(0, max(1, n // 4))):
                h[rng.randint(0, n - 1)] = rng.randint(1, 1000000000)

    out.append(str(n))
    out.append(" ".join(map(str, h)))

    # Queries: keep count modest for brute speed.
    maxq = min(40, n * (n + 1) // 2)
    q = rng.randint(1, max(1, maxq))
    out.append(str(q))
    # Guarantee coverage of edge query types when applicable.
    must = []
    must.append((1, 1))                       # width-1 at start
    must.append((n, n))                       # width-1 at end
    if n >= 2:
        must.append((1, n))                   # full range
        must.append((1, 2))                   # width-2 at start
        must.append((n - 1, n))               # width-2 at end
        mid = (n + 1) // 2
        must.append((mid, mid))               # width-1 in middle
    must = [(l, r) for (l, r) in must if 1 <= l <= r <= n]
    rng.shuffle(must)
    must = must[: min(len(must), q)]
    queries = list(must)
    while len(queries) < q:
        l = rng.randint(1, n)
        r = rng.randint(l, n)
        queries.append((l, r))
    for (l, r) in queries:
        out.append(f"{l} {r}")


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    out = []
    gen_case(rng, out)
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
