import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    chars = ([chr(c) for c in range(ord('0'), ord('9') + 1)] +
             [chr(c) for c in range(ord('A'), ord('Z') + 1)] +
             [chr(c) for c in range(ord('a'), ord('z') + 1)])

    T = rng.randint(1, 5)
    print(T)

    for _ in range(T):
        choice = rng.randint(0, 3)
        if choice == 0:
            # edge: single character (freq 1 -> not prime -> empty)
            print(rng.choice(chars))
        elif choice == 1:
            # edge: all same character, count may or may not be prime
            n = rng.randint(1, 20)
            print(rng.choice(chars) * n)
        elif choice == 2:
            # edge: all distinct (every freq 1 -> empty)
            n = rng.randint(1, 15)
            print(''.join(rng.sample(chars, n)))
        else:
            # general random string
            n = rng.randint(1, 40)
            print(''.join(rng.choice(chars) for _ in range(n)))


main()
