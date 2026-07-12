import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    r = rng.random()

    if r < 0.20:
        # boundary / extreme n values (brute handles via period reduction)
        n = rng.choice([0, 1, 2, 3, 2147483647, 2147483646, 2147483645,
                        1000000000, 999999999])
    elif r < 0.35:
        # boundary m values with small n
        n = rng.randint(0, 100000)
        m = rng.choice([0, 1, 2, 3, 17, 18, 19])
        print(n, m)
        return
    elif r < 0.70:
        # small random n (pure-iteration friendly)
        n = rng.randint(0, 1000000)
    else:
        # full-range random n
        n = rng.randint(0, 2147483647)

    m = rng.randint(0, 19)
    print(n, m)


main()
