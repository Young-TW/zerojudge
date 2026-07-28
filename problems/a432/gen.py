#!/usr/bin/env python3
import sys, random, string

def main():
    if len(sys.argv) != 2:
        return
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    # always output exactly one poem
    print(1)

    if seed == 0:
        # empty poem
        N, L, P = 0, 1, 1
        print(N, L, P)
        # no sentences
        return

    if seed == 1:
        # single short sentence, minimal values
        N, L, P = 1, 5, 2
        print(N, L, P)
        print('a' * 5)
        return

    if seed == 2:
        # many identical sentences, L equals sentence length
        N, L, P = 1000, 50, 5
        print(N, L, P)
        line = 'x' * 50
        for _ in range(N):
            print(line)
        return

    # general random case
    N = rnd.randint(1, 5000)
    L = rnd.randint(1, 10**9)
    P = rnd.randint(1, 10)
    print(N, L, P)

    # allowed characters: ASCII 33..127 except '-'
    allowed = [c for c in (string.printable + string.punctuation + string.ascii_letters + string.digits)
               if 33 <= ord(c) <= 127 and c != '-']

    for _ in range(N):
        length = rnd.randint(1, 100)
        sentence = ''.join(rnd.choice(allowed) for _ in range(length))
        print(sentence)

if __name__ == "__main__":
    main()
