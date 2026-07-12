import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    mode = seed % 7

    if mode == 0:
        # 1x1 grid
        m, n = 1, 1
    elif mode == 1:
        # single row
        m, n = 1, rng.randint(1, 15)
    elif mode == 2:
        # single column
        m, n = rng.randint(1, 15), 1
    elif mode == 3:
        # all X (zero components)
        m, n = rng.randint(1, 10), rng.randint(1, 10)
        print(m, n)
        for _ in range(m):
            print('X' * n)
        return
    elif mode == 4:
        # all J (one big component)
        m, n = rng.randint(1, 10), rng.randint(1, 10)
        print(m, n)
        for _ in range(m):
            print('J' * n)
        return
    elif mode == 5:
        # checkerboard: every J isolated (4-connectivity)
        m, n = rng.randint(2, 10), rng.randint(2, 10)
        print(m, n)
        for i in range(m):
            row = []
            for j in range(n):
                if (i + j) % 2 == 0:
                    row.append('J')
                else:
                    row.append('X')
            print(''.join(row))
        return
    else:
        # general random
        m, n = rng.randint(1, 20), rng.randint(1, 20)

    print(m, n)
    for _ in range(m):
        row = []
        for _ in range(n):
            row.append(rng.choice(['X', 'J']))
        print(''.join(row))


main()
