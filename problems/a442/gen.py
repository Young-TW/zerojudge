import sys
import random


def main():
    rnd = random.Random(int(sys.argv[1]))
    num_cases = rnd.randint(1, 8)
    for _ in range(num_cases):
        n = rnd.randint(1, 30)
        a = ''.join(str(rnd.randint(0, 9)) for _ in range(n))
        mode = rnd.choice(['rot', 'flip', 'flip_rot', 'random'])
        if mode == 'rot':
            shift = rnd.randint(0, n - 1)
            b = a[shift:] + a[:shift]
        elif mode == 'flip':
            b = a[::-1]
        elif mode == 'flip_rot':
            rev = a[::-1]
            shift = rnd.randint(0, n - 1)
            b = rev[shift:] + rev[:shift]
        else:
            b = ''.join(str(rnd.randint(0, 9)) for _ in range(n))
        print(a)
        print(b)


main()
