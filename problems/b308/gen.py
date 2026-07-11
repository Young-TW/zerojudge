import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    T = rng.randint(1, 10)
    print(T)
    
    for _ in range(T):
        inko = [rng.randint(0, 10) for _ in range(5)]
        print(' '.join(map(str, inko)))
        
        doctor = [rng.randint(0, 10) for _ in range(5)]
        print(' '.join(map(str, doctor)))
        
        if rng.random() < 0.1:
            p = rng.randint(500, 1000)
        else:
            p = rng.randint(0, 499)
        print(p)

if __name__ == '__main__':
    main()
