import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    while True:
        N = rng.randint(1, 20)
        M = rng.randint(1, N)
        
        intervals = []
        for _ in range(M):
            S = rng.randint(0, N)
            E = rng.randint(S, N)
            intervals.append((S, E))
            
        covered = [False] * N
        for S, E in intervals:
            for i in range(S, E):
                covered[i] = True
                
        if not all(covered):
            break
            
    print(f"{N} {M}")
    for S, E in intervals:
        print(f"{S} {E}")

if __name__ == "__main__":
    main()
