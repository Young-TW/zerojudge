import sys, random


def main():
    rnd = random.Random(int(sys.argv[1]))

    # Keep the size small so the O(n^4)-ish brute finishes well under 1s.
    T = rnd.randint(1, 3)
    out = [str(T)]

    for _ in range(T):
        n = rnd.randint(1, 12)
        out.append(str(n))

        # Mix value regimes to exercise boundary + non-trivial structure.
        ids = []
        for _ in range(n):
            r = rnd.random()
            if r < 0.10:
                ids.append(1)                    # isolated vertex
            elif r < 0.22:
                ids.append(rnd.choice([2, 3, 5, 7]))  # small primes
            elif r < 0.42:
                ids.append(rnd.randint(2, 20))   # many shared factors
            elif r < 0.62:
                ids.append(rnd.randint(2, 100))  # richer gcd graph
            elif r < 0.80:
                ids.append(rnd.randint(2, 30000))  # upper boundary values
            else:
                ids.append(rnd.choice(
                    [1, 2, 4, 8, 12, 15, 30, 210, 2310, 30030][:10]))
            out.append(str(ids[-1]))

    print("\n".join(out))


main()
