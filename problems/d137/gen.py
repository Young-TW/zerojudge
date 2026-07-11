import sys
import random

def gen_real(rng):
    a = rng.randint(-100, 100)
    if a == 0:
        return "0"
    sign = ""
    if a > 0 and rng.random() < 0.5:
        sign = "+"
    return f"{sign}{a}"

def gen_imag(rng):
    b = rng.randint(-100, 100)
    if b == 0:
        b = 1
    if b == 1:
        if rng.random() < 0.5:
            return "i"
        else:
            return "+i"
    elif b == -1:
        return "-i"
    elif b > 1:
        if rng.random() < 0.5:
            return f"{b}i"
        else:
            return f"+{b}i"
    else:
        return f"{b}i"

def gen_complex(rng):
    a = rng.randint(-100, 100)
    b = rng.randint(-100, 100)
    if a == 0:
        a = 1
    if b == 0:
        b = 1
        
    if a > 0:
        if rng.random() < 0.5:
            a_str = f"+{a}"
        else:
            a_str = f"{a}"
    else:
        a_str = f"{a}"
        
    if b == 1:
        b_str = "+i"
    elif b == -1:
        b_str = "-i"
    elif b > 1:
        b_str = f"+{b}i"
    else:
        b_str = f"{b}i"
        
    return a_str + b_str

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    n = rng.randint(10, 20)
    for _ in range(n):
        choice = rng.randint(0, 2)
        if choice == 0:
            print(gen_real(rng))
        elif choice == 1:
            print(gen_imag(rng))
        else:
            print(gen_complex(rng))

if __name__ == "__main__":
    main()
