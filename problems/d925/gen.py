import sys
import random

def main():
    if len(sys.argv) < 2:
        return
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    M = rng.randint(1, 10)
    N = rng.randint(1, 10)
    T = rng.randint(1, 10)
    
    print(f"{M} {N} {T}")
    for _ in range(T):
        Xi = rng.randint(1, M)
        Yi = rng.randint(1, N)
        Ki = rng.randint(1, 1024)
        print(f"{Xi} {Yi} {Ki}")

if __name__ == "__main__":
    main()
