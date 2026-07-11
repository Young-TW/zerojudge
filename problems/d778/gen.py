import sys
import random

def main():
    if len(sys.argv) < 2:
        seed = 0
    else:
        seed = int(sys.argv[1])
        
    rng = random.Random(seed)
    
    n = rng.randint(1, 5)
    print(n)
    
    for _ in range(n):
        a1 = rng.randint(1, 100)
        k1 = rng.randint(1, 20)
        a0 = a1 * k1
        
        b0 = rng.randint(1, 100)
        k2 = rng.randint(1, 20)
        b1 = b0 * k2
        
        print(f"{a0} {a1} {b0} {b1}")

if __name__ == "__main__":
    main()
