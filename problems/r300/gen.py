import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    N = rng.randint(1, 10)
    M = rng.randint(1, 10)
    K = rng.randint(0, N)
    
    A = []
    cur = 0
    for _ in range(N):
        cur += rng.randint(0, 5)
        A.append(cur)
        
    B = []
    cur = 0
    for _ in range(M):
        cur += rng.randint(0, 5)
        B.append(cur)
        
    print(N, M, K)
    print(" ".join(map(str, A)))
    print(" ".join(map(str, B)))

if __name__ == "__main__":
    main()
