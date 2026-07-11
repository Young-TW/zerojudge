import sys
import random

def main():
    if len(sys.argv) < 2:
        seed = 0
    else:
        seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    N = rng.randint(1, 15)
    K = rng.randint(1, N)
    
    arr = [rng.randint(-100, 100) for _ in range(N)]
    
    print(f"{N} {K}")
    print(" ".join(map(str, arr)))

if __name__ == "__main__":
    main()
