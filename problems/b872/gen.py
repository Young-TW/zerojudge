import sys
import random

def main():
    if len(sys.argv) < 2:
        seed = 0
    else:
        seed = int(sys.argv[1])
    
    rng = random.Random(seed)
    
    T = rng.randint(1, 5)
    print(T)
    
    for _ in range(T):
        N = rng.randint(1, 50)
        print(N)
        
        points = set()
        while len(points) < N:
            x = rng.randint(-100, 100)
            y = rng.randint(-100, 100)
            points.add((x, y))
            
        for x, y in points:
            print(f"{x} {y}")

if __name__ == "__main__":
    main()
