import sys
from random import Random

BOUND = (1 << 31) - 1
LIMIT = 1 << 62


def cdiv(a, b):
    q = abs(a) // abs(b)
    return -q if (a < 0) != (b < 0) else q


def cmod(a, b):
    r = abs(a) % abs(b)
    return r if a >= 0 else -r


def gen(rng, depth):
    if depth == 0 or rng.random() < 0.35:
        r = rng.random()
        if r < 0.15:
            v = 0
        elif r < 0.25:
            v = 1
        elif r < 0.30:
            v = BOUND
        else:
            v = rng.randint(0, 100)
        return [str(v)], v
    op = rng.choice(['+', '-', '*', '/', '%'])
    lt, lv = gen(rng, depth - 1)
    rt, rv = gen(rng, depth - 1)
    if op == '+':
        v = lv + rv
    elif op == '-':
        v = lv - rv
    elif op == '*':
        v = lv * rv
    elif op == '/':
        if rv == 0:
            raise ValueError
        v = cdiv(lv, rv)
    else:
        if rv == 0:
            raise ValueError
        v = cmod(lv, rv)
    if abs(v) > LIMIT:
        raise ValueError
    if rng.random() < 0.3:
        toks = ['('] + lt + [op] + rt + [')']
    else:
        toks = lt + [op] + rt
    return toks, v


def main():
    rng = Random(int(sys.argv[1]))
    for _ in range(1000):
        try:
            depth = rng.randint(1, 4)
            toks, _ = gen(rng, depth)
            print(' '.join(toks))
            return
        except ValueError:
            continue


if __name__ == '__main__':
    main()
