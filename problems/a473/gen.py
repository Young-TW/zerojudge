import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    LLONG_MAX = (1 << 63) - 1
    LLONG_MIN = -(1 << 63)

    mode = rng.randint(0, 7)

    if mode == 0:
        # Boundary: N = 1
        N = 1
        lo, hi = -10, 10
    elif mode == 1:
        # Sample size: N = 2
        N = 2
        lo, hi = -50, 50
    elif mode == 2:
        # Small N, moderate values
        N = rng.randint(2, 8)
        lo, hi = -1000, 1000
    elif mode == 3:
        # Medium N, small values
        N = rng.randint(8, 20)
        lo, hi = -100, 100
    elif mode == 4:
        # Large values (intermediate products may overflow long long)
        N = rng.randint(1, 4)
        lo, hi = -2000000000, 2000000000
    elif mode == 5:
        # All zeros
        N = rng.randint(1, 15)
        lo, hi = 0, 0
    elif mode == 6:
        # Tiny range including negatives
        N = rng.randint(1, 10)
        lo, hi = -5, 5
    else:
        # Extreme values near long long boundaries
        N = rng.randint(1, 3)
        choices = [0, 1, -1, LLONG_MAX, LLONG_MIN, LLONG_MAX - 1, LLONG_MIN + 1]

    if mode == 7:
        A = [[rng.choice(choices) for _ in range(N)] for _ in range(N)]
        B = [[rng.choice(choices) for _ in range(N)] for _ in range(N)]
    else:
        A = [[rng.randint(lo, hi) for _ in range(N)] for _ in range(N)]
        B = [[rng.randint(lo, hi) for _ in range(N)] for _ in range(N)]

    # True C = A * B  (Python big ints, no overflow)
    C_true = [[sum(A[i][k] * B[k][j] for k in range(N)) for j in range(N)]
              for i in range(N)]

    fits = all(LLONG_MIN <= C_true[i][j] <= LLONG_MAX
               for i in range(N) for j in range(N))

    make_yes = rng.random() < 0.5

    if make_yes and fits:
        C = [row[:] for row in C_true]
    else:
        # NO case: start from (clamped) true C, then perturb
        if fits:
            C = [row[:] for row in C_true]
        else:
            C = [[max(LLONG_MIN, min(LLONG_MAX, v)) for v in row]
                 for row in C_true]
        num = rng.randint(1, max(1, N))
        for _ in range(num):
            i = rng.randint(0, N - 1)
            j = rng.randint(0, N - 1)
            delta = rng.choice([1, -1])
            C[i][j] = max(LLONG_MIN, min(LLONG_MAX, C[i][j] + delta))

    lines = [str(N)]
    for row in A:
        lines.append(' '.join(str(x) for x in row))
    for row in B:
        lines.append(' '.join(str(x) for x in row))
    for row in C:
        lines.append(' '.join(str(x) for x in row))
    sys.stdout.write('\n'.join(lines) + '\n')


main()
