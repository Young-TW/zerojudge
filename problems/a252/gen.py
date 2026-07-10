import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Lengths kept small so the brute-force (2^n enumeration) runs well under 1s.
    # 10% chance of an empty string to cover the lower boundary.
    def gen_len():
        if rng.random() < 0.1:
            return 0
        return rng.randint(1, 15)

    L1, L2, L3 = gen_len(), gen_len(), gen_len()

    # Sometimes use a tiny alphabet so the three strings share many characters
    # (forces non-trivial LCS); sometimes a full lowercase alphabet.
    alpha_size = rng.choice([1, 2, 3, 4, 8, 26])
    alphabet = [chr(ord('a') + i) for i in range(alpha_size)]

    def gen(L):
        return ''.join(rng.choice(alphabet) for _ in range(L))

    print(gen(L1))
    print(gen(L2))
    print(gen(L3))


main()
