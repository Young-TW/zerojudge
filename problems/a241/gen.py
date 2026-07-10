import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    m = rng.randint(1, 6)
    print(m)
    for _ in range(m):
        choice = rng.randint(0, 2)
        if choice == 0:
            n = rng.choice([1, 2, 3, 4, 5, 10, 25, 50, 100])
        elif choice == 1:
            n = rng.randint(1, 50)
        else:
            n = rng.randint(1, 2000)
        print(n)

main()
