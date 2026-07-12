import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    T = rng.randint(1, 5)
    print(T)
    for _ in range(T):
        choice = rng.randint(0, 2)
        if choice == 0:
            N = rng.randint(2, 5)
        elif choice == 1:
            N = rng.randint(2, 50)
        else:
            N = rng.randint(2, 200)
        print(N)
        edges = []
        for u in range(1, N + 1):
            v = rng.randint(1, N)
            while v == u:
                v = rng.randint(1, N)
            edges.append((u, v))
        rng.shuffle(edges)
        for u, v in edges:
            print(u, v)


main()
