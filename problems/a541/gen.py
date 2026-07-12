import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    r = rng.randint(0, 4)
    if r == 0:
        N = 1
    elif r == 1:
        N = 2
    elif r == 2:
        N = rng.randint(3, 20)
    elif r == 3:
        N = rng.randint(20, 200)
    else:
        N = rng.randint(1, 10)

    out = [str(N)]

    alphabet = "abcdefghijklmnopqrstuvwxyz"

    def rand_word(min_len=1, max_len=19):
        ln = rng.randint(min_len, max_len)
        return ''.join(rng.choice(alphabet) for _ in range(ln))

    known = []
    seen = set()
    for _ in range(N):
        attempts = 0
        while True:
            w = rand_word(1, 19)
            if w not in seen:
                seen.add(w)
                known.append(w)
                break
            attempts += 1
            if attempts > 1000:
                w = rand_word(1, 19)
                while w in seen:
                    w = rand_word(1, 19)
                seen.add(w)
                known.append(w)
                break
    for w in known:
        out.append(w)

    if rng.randint(0, 1) == 0:
        Q = rng.randint(1, 20)
    else:
        Q = rng.randint(1, 300)

    out.append(str(Q))

    for _ in range(Q):
        qr = rng.randint(0, 2)
        if qr == 0 and len(known) > 0:
            w = rng.choice(known)
        elif qr == 1 and len(seen) > 0:
            w = rng.choice(list(seen))
        else:
            attempts = 0
            while True:
                w = rand_word(1, 19)
                if w not in seen or attempts > 1000:
                    break
                attempts += 1
        out.append(w)

    sys.stdout.write('\n'.join(out) + '\n')


main()
