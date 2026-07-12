import sys
import random


def rand_numstr(rng, max_digits):
    """Random non-negative integer as a decimal string, possibly with leading
    zeros (to exercise the brute's normalization path). Length in [1, max_digits]."""
    length = rng.randint(1, max_digits)
    return ''.join(str(rng.randint(0, 9)) for _ in range(length))


def gen_one(rng):
    """Produce one (a, b) pair covering a variety of boundary cases."""
    mode = rng.randint(0, 9)
    if mode == 0:
        # both zero (with possible leading zeros)
        a = '0' * rng.randint(1, 4)
        b = '0' * rng.randint(1, 4)
    elif mode == 1:
        # one zero, one normal
        a = '0'
        b = rand_numstr(rng, 40)
    elif mode == 2:
        a = rand_numstr(rng, 40)
        b = '0'
    elif mode == 3:
        # single digit each
        a = str(rng.randint(0, 9))
        b = str(rng.randint(0, 9))
    elif mode == 4:
        # one digit, one multi-digit with leading zeros
        a = str(rng.randint(1, 9))
        b = '0' * rng.randint(0, 3) + rand_numstr(rng, 20)
    elif mode == 5:
        # both small-ish
        a = rand_numstr(rng, 30)
        b = rand_numstr(rng, 30)
    elif mode == 6:
        # one large, one small
        a = rand_numstr(rng, 200)
        b = rand_numstr(rng, 5)
    elif mode == 7:
        a = rand_numstr(rng, 5)
        b = rand_numstr(rng, 200)
    elif mode == 8:
        # both moderately large
        a = rand_numstr(rng, 150)
        b = rand_numstr(rng, 150)
    else:
        # both large (still tiny vs the real 2^17-digit limit)
        a = rand_numstr(rng, 200)
        b = rand_numstr(rng, 200)
    # ensure non-empty
    if a == '':
        a = '0'
    if b == '':
        b = '0'
    return a, b


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # 1 to 3 test cases (problem allows up to 10; keep small for brute speed).
    cases = rng.randint(1, 3)

    lines = []
    for _ in range(cases):
        a, b = gen_one(rng)
        # Emulate the sample format: put a, b on their own lines, and a blank
        # line between consecutive pairs (whitespace is ignored by readers).
        lines.append(a)
        lines.append(b)
        lines.append('')

    sys.stdout.write('\n'.join(lines).rstrip('\n') + '\n')


if __name__ == '__main__':
    main()
