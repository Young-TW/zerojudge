import sys
import random

def gen(rng):
    r = rng.random()
    if r < 0.10:
        # Same start and target -> answer 0
        s = ''.join(str(rng.randint(0, 9)) for _ in range(6))
        return s, s
    elif r < 0.15:
        # All zeros to all nines
        return '000000', '999999'
    elif r < 0.20:
        # All nines to all zeros
        return '999999', '000000'
    elif r < 0.30:
        # Start is all same digit
        d = rng.randint(0, 9)
        s = str(d) * 6
        t = ''.join(str(rng.randint(0, 9)) for _ in range(6))
        return s, t
    elif r < 0.35:
        # Target is all same digit
        d = rng.randint(0, 9)
        t = str(d) * 6
        s = ''.join(str(rng.randint(0, 9)) for _ in range(6))
        return s, t
    elif r < 0.45:
        # Only one digit differs
        s = ''.join(str(rng.randint(0, 9)) for _ in range(6))
        t = list(s)
        pos = rng.randint(0, 5)
        new_d = rng.randint(0, 9)
        while new_d == int(t[pos]):
            new_d = rng.randint(0, 9)
        t[pos] = str(new_d)
        return s, ''.join(t)
    elif r < 0.55:
        # Permutation of start digits (test swaps)
        s = ''.join(str(rng.randint(0, 9)) for _ in range(6))
        t = list(s)
        rng.shuffle(t)
        return s, ''.join(t)
    elif r < 0.60:
        # Leading zeros: start begins with 0
        s = '0' + ''.join(str(rng.randint(0, 9)) for _ in range(5))
        t = ''.join(str(rng.randint(0, 9)) for _ in range(6))
        return s, t
    else:
        # Fully random
        s = ''.join(str(rng.randint(0, 9)) for _ in range(6))
        t = ''.join(str(rng.randint(0, 9)) for _ in range(6))
        return s, t

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    s, t = gen(rng)
    print(f"{s} {t}")

if __name__ == '__main__':
    main()
