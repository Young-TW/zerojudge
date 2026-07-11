import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    N = rng.randint(2, 12)
    print(N)
    
    ids = list(range(1, N))
    rng.shuffle(ids)
    
    for i in range(N - 1):
        u = rng.randint(1, i + 1)
        v = i + 2
        w = rng.randint(1, 15)
        print(ids[i], u, v, w)
    
    Q = rng.randint(1, 12)
    print(Q)
    
    for _ in range(Q):
        A = rng.randint(1, N)
        B = rng.randint(1, N)
        k = rng.randint(1, 20)
        print(A, B, k)

main()
