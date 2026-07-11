import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    T = rng.randint(1, 10)
    print(T)
    for _ in range(T):
        choice = rng.randint(0, 3)
        if choice == 0:
            N = rng.randint(2, 1000)
        elif choice == 1:
            N = rng.randint(1000, 10**6)
        elif choice == 2:
            N = rng.randint(10**6, 10**9)
        else:
            N = rng.randint(10**9, 10**12)
        print(N)

if __name__ == "__main__":
    main()
