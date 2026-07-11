import sys
import random

def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    rng = random.Random(seed)
    
    N = rng.randint(10, 50)
    Q = rng.randint(10, 50)
    
    print(f"{N} {Q}")
    
    delays = [rng.randint(1, 100) for _ in range(N)]
    print(" ".join(map(str, delays)))
    
    for i in range(2, N + 1):
        parent = rng.randint(1, i - 1)
        print(f"{i} {parent}")
        
    for _ in range(Q):
        if rng.random() < 0.3:
            a = rng.randint(1, N)
            b = rng.randint(1, 100)
            print(f"0 {a} {b}")
        else:
            k = rng.randint(1, N)
            a = rng.randint(1, N)
            b = rng.randint(1, N)
            print(f"{k} {a} {b}")

if __name__ == "__main__":
    main()
