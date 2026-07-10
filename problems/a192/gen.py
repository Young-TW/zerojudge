import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    MAXV = 2147483646
    mode = rng.randint(0, 9)

    if mode == 0:
        # U=1 boundary
        U = 1
        L = rng.randint(1, 8)
    elif mode == 1:
        # U=L, all lower used
        n = rng.randint(1, 6)
        U = L = n
    elif mode == 2:
        # U=L=1
        U = L = 1
    elif mode == 3:
        # single upper, many lower
        L = rng.randint(3, 8)
        U = 1
    elif mode == 4:
        # near-max positions (overflow)
        L = rng.randint(2, 6)
        U = rng.randint(1, L)
    elif mode == 5:
        # L >> U
        L = 8
        U = rng.randint(1, 3)
    elif mode == 6:
        # all identical positions
        L = rng.randint(2, 6)
        U = rng.randint(1, L)
    elif mode == 7:
        # duplicates in upper
        L = rng.randint(3, 7)
        U = rng.randint(2, L)
    elif mode == 8:
        # U=L, small
        n = rng.randint(2, 7)
        U = L = n
    else:
        # general small
        L = rng.randint(1, 8)
        U = rng.randint(1, L)

    def gen(n, kind):
        if kind == "max":
            base = rng.randint(MAXV - 15, MAXV)
            return sorted(rng.randint(max(1, base - 20), base) for _ in range(n))
        if kind == "same":
            return [rng.randint(1, 100)] * n
        if kind == "dup":
            v = rng.randint(1, 100)
            vals = [v, v]
            vals += [rng.randint(v, v + 40) for _ in range(n - 2)]
            return sorted(vals)
        # normal
        base = rng.randint(1, 100)
        spread = rng.randint(0, 60)
        return sorted(rng.randint(base, base + spread) for _ in range(n))

    if mode == 4:
        up, lo = gen(U, "max"), gen(L, "max")
    elif mode == 6:
        up, lo = gen(U, "same"), gen(L, "same")
    elif mode == 7:
        up, lo = gen(U, "dup"), gen(L, "normal")
    else:
        up, lo = gen(U, "normal"), gen(L, "normal")

    print(f"{U} {L}")
    print(" ".join(map(str, up)))
    print(" ".join(map(str, lo)))


if __name__ == "__main__":
    main()
