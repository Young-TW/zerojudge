import sys
import random

def main():
    if len(sys.argv) < 2:
        return
    rng = random.Random(int(sys.argv[1]))
    
    T = rng.randint(1, 10)
    print(T)
    for _ in range(T):
        N = rng.randint(0, 1000)
        M = rng.randint(1, 10)
        print(f"{N} {M}")
        w = [str(rng.randint(0, 1000)) for _ in range(M)]
        print(" ".join(w))

if __name__ == "__main__":
    main()
