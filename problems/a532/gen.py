import sys
import random

def main():
    rng = random.Random(int(sys.argv[1]))
    n_cases = rng.randint(3, 8)
    edge_cases = [1, 2, 3, 4, 5, 7, 8, 19, 20, 39, 40, 99, 100, 199, 200]
    for _ in range(n_cases):
        if rng.random() < 0.4:
            n = rng.choice(edge_cases)
        else:
            n = rng.randint(1, 200)
        print(n)
    print(0)

main()
