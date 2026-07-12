import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    MAX_P = 10 ** 101

    r = rng.randint(0, 9)

    if r == 0:
        # n = 1 boundary
        n = 1
        k = rng.randint(1, 500)
    elif r == 1:
        # n = 200 boundary (k can only be 1..3)
        n = 200
        k = rng.randint(1, 3)
    elif r == 2:
        # k = 1 boundary
        n = rng.randint(1, 200)
        k = 1
    elif r == 3:
        # k = 2, large n
        n = rng.randint(100, 200)
        k = 2
    elif r == 4:
        # p near max: 10^100
        n = 100
        k = 10
    elif r == 5:
        # n = 2
        n = 2
        k = rng.randint(1, 500)
    elif r == 6:
        # moderate n and k
        n = rng.randint(3, 30)
        k = rng.randint(2, 100)
    elif r == 7:
        # p at max boundary: 10^101
        n = 101
        k = 10
    else:
        # general random: pick k, then find max valid n
        k = rng.randint(1, 300)
        if k == 1:
            n = rng.randint(1, 200)
        else:
            max_n = 1
            val = k
            while val * k <= MAX_P and max_n < 200:
                val *= k
                max_n += 1
            n = rng.randint(1, max_n)

    p = k ** n

    assert 1 <= n <= 200
    assert 1 <= k <= 10 ** 9
    assert 1 <= p <= MAX_P

    print(n)
    print(p)


main()
