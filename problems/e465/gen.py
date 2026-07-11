import sys
import random

def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    rng = random.Random(seed)
    
    N = rng.randint(1, 20)
    M = rng.randint(N, 200)
    S = rng.randint(1, M)
    
    cuts = sorted(rng.randint(0, M) for _ in range(N + 1))
    x = [cuts[i+1] - cuts[i] for i in range(N)]
    
    print(f"{M} {S} {N}")
    print(" ".join(map(str, x)))

if __name__ == "__main__":
    main()
