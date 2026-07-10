import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    T = rng.randint(1, 5)
    out = [str(T)]

    for _ in range(T):
        scenario = rng.randint(0, 7)

        if scenario == 0:
            # General small random
            N = rng.randint(1, 30)
            M = rng.randint(1, 10)
            max_drive = rng.randint(0, 15)
            A = [rng.randint(0, max_drive) for _ in range(N)]
        elif scenario == 1:
            # All same drive
            N = rng.randint(1, 30)
            M = rng.randint(1, 10)
            A = [rng.randint(0, 15)] * N
        elif scenario == 2:
            # All distinct, M >= N -> 0 swaps
            N = rng.randint(1, 20)
            M = rng.randint(N, N + 5)
            A = list(range(N))
            rng.shuffle(A)
        elif scenario == 3:
            # All distinct, M = 1 -> N-1 swaps
            N = rng.randint(1, 25)
            M = 1
            A = list(range(N))
            rng.shuffle(A)
        elif scenario == 4:
            # Two drives alternating (or same drive)
            N = rng.randint(2, 30)
            M = rng.randint(1, 3)
            d1 = rng.randint(0, 15)
            d2 = rng.randint(0, 15)
            A = [d1 if i % 2 == 0 else d2 for i in range(N)]
        elif scenario == 5:
            # Drive 0 mixed in
            N = rng.randint(1, 30)
            M = rng.randint(1, 10)
            A = []
            for _ in range(N):
                if rng.random() < 0.5:
                    A.append(0)
                else:
                    A.append(rng.randint(1, 10))
        elif scenario == 6:
            # Repeated pattern
            N = rng.randint(1, 30)
            M = rng.randint(1, 5)
            plen = rng.randint(1, min(N, 8))
            pat = [rng.randint(0, 10) for _ in range(plen)]
            A = [pat[i % plen] for i in range(N)]
        else:
            # N = 1 edge case
            N = 1
            M = rng.randint(1, 5)
            A = [rng.randint(0, 10)]

        out.append(f"{N} {M}")
        out.append(" ".join(map(str, A)))

    print("\n".join(out))


main()
