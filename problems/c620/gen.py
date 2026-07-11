import sys
import random

def main():
    if len(sys.argv) < 2:
        seed = 0
    else:
        seed = int(sys.argv[1])
        
    rng = random.Random(seed)
    
    n = rng.randint(1, 10)
    m = rng.randint(1, 10)
    
    max_val_choices = [n * m, n * m // 2 + 1, 2**31 - 2, 100, 5]
    max_val = rng.choice(max_val_choices)
    
    print(f"{n} {m}")
    for _ in range(n):
        row = [str(rng.randint(0, max_val)) for _ in range(m)]
        print(" ".join(row))

if __name__ == "__main__":
    main()
