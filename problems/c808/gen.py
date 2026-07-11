import sys
import random

def main():
    if len(sys.argv) < 2:
        return
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    N = rng.randint(8, 12)
    M = rng.randint(5, 10)
    
    print(N, M)
    for _ in range(M):
        x = rng.randint(0, 1)
        k = rng.randint(1, N)
        print(x, k)

if __name__ == '__main__':
    main()
