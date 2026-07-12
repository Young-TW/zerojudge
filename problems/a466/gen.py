import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    n = rng.randint(1, 10)
    candidates = ["one", "two", "three"]
    letters = "abcdefghijklmnopqrstuvwxyz"
    out = [str(n)]
    for _ in range(n):
        word = rng.choice(candidates)
        # at most one wrong letter (possibly zero)
        if rng.random() < 0.5:
            pos = rng.randrange(len(word))
            c = rng.choice(letters)
            word = word[:pos] + c + word[pos + 1:]
        out.append(word)
    sys.stdout.write("\n".join(out) + "\n")


main()
