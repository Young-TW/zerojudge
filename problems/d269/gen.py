import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    t = rng.randint(1, 5)
    print(t)
    for _ in range(t):
        n = rng.randint(3, 10)
        nums = [round(rng.uniform(0.1, 100000.0), 2) for _ in range(n)]
        print(n, end="")
        for num in nums:
            print(f" {num}", end="")
        print()

if __name__ == "__main__":
    main()
