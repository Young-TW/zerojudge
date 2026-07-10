import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    lines = []
    num_lines = rng.randint(1, 5)
    for _ in range(num_lines):
        length = rng.choice([1, 2, 3, 8, 20, 40])
        chars = []
        # Track whether we just emitted a sentence ender so the next token
        # tends to start a new sentence (good coverage), but we also allow
        # arbitrary sequences.
        sentence_end = rng.choice([True, False])
        for _ in range(length):
            r = rng.random()
            if r < 0.55:
                # a word of 1-4 lowercase letters
                wlen = rng.randint(1, 4)
                # bias toward single 'i' sometimes to exercise the standalone-i rule
                if rng.random() < 0.2:
                    wlen = 1
                word = []
                for _ in range(wlen):
                    # bias toward 'i' for boundary coverage
                    if rng.random() < 0.15:
                        word.append('i')
                    else:
                        word.append(chr(rng.randint(ord('a'), ord('z'))))
                chars.append(''.join(word))
            elif r < 0.75:
                chars.append(' ')  # space
            elif r < 0.85:
                chars.append(',')
            elif r < 0.92:
                chars.append('.')
                sentence_end = True
            elif r < 0.97:
                chars.append('!')
                sentence_end = True
            else:
                chars.append('?')
                sentence_end = True
        # Join without adding/removing spaces; keep raw token list as a string
        line = ''.join(chars)
        # Guarantee only allowed characters slipped in (defensive)
        allowed = set("abcdefghijklmnopqrstuvwxyz ,.!?")
        line = ''.join(ch for ch in line if ch in allowed)
        # Ensure non-empty-ish but allow empty lines too as a boundary case
        lines.append(line)
    sys.stdout.write('\n'.join(lines) + '\n')


main()
