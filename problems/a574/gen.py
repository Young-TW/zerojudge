import sys
import random


def rval(rnd):
    r = rnd.random()
    if r < 0.20:
        return 0
    if r < 0.40:
        return 100
    return rnd.randint(0, 100)


def main():
    rnd = random.Random(int(sys.argv[1]))
    d = 10

    # Number of data points: keep small so brute force runs well under 1s,
    # but vary to cover edges (including N=1).
    N = rnd.randint(1, 100)

    out = []
    for _ in range(N):
        out.append(",".join(str(rval(rnd)) for _ in range(d)))
    out.append("-1")

    # Number of queries: small (brute is O(N*Q*d)), cover a few edge types.
    Q = rnd.randint(1, 8)
    for q in range(Q):
        L = [rval(rnd) for _ in range(d)]
        U = [rval(rnd) for _ in range(d)]
        # ensure L[i] <= U[i]
        for i in range(d):
            if L[i] > U[i]:
                L[i], U[i] = U[i], L[i]

        # Occasionally inject boundary query types.
        mode = rnd.randint(0, 3)
        if mode == 0:
            # match-everything query
            L = [0] * d
            U = [100] * d
        elif mode == 1:
            # single-value query (L == U)
            v = rval(rnd)
            L = [v] * d
            U = [v] * d
        elif mode == 2:
            # tight window around boundaries
            L = [rnd.choice([0, 0, 1]) for _ in range(d)]
            U = [rnd.choice([100, 100, 99]) for _ in range(d)]
            for i in range(d):
                if L[i] > U[i]:
                    L[i], U[i] = U[i], L[i]

        out.append(",".join(map(str, L)))
        out.append(",".join(map(str, U)))
        out.append("-1")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
