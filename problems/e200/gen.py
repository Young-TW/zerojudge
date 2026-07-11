import sys
import random

def main():
    if len(sys.argv) < 2:
        return
    seed = int(sys.argv[1])
    rnd = random.Random(seed)
    
    T = rnd.randint(1, 5)
    print(T)
    
    for _ in range(T):
        N = rnd.randint(2, 10)
        M = rnd.randint(1, 10)
        print(N, M)
        
        for _ in range(M):
            a = rnd.randint(1, N)
            b = rnd.randint(1, N)
            while a == b:
                b = rnd.randint(1, N)
            w = rnd.randint(1, 10)
            print(a, b, w)

if __name__ == '__main__':
    main()
