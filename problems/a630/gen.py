import sys
import random

def digit_to_char(d):
    if d < 10:
        return str(d)
    return chr(ord('a') + d - 10)

def gen_number(rng, base):
    if rng.random() < 0.1:
        return '0'
    length = rng.randint(1, 4)
    digits = [rng.randint(1, base - 1)]
    for _ in range(length - 1):
        digits.append(rng.randint(0, base - 1))
    return ''.join(digit_to_char(d) for d in digits)

def main():
    rng = random.Random(int(sys.argv[1]))
    num_terms = rng.randint(2, 5)
    parts = []
    for i in range(num_terms):
        base = rng.randint(2, 20)
        num = gen_number(rng, base)
        if i == 0:
            parts.append('{}^{}'.format(num, base))
        else:
            op = rng.choice(['+', '-', '*'])
            parts.append('{}{}^{}'.format(op, num, base))
    out_base = rng.randint(2, 20)
    parts.append('=^{}'.format(out_base))
    print(''.join(parts))

main()
