import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    text = []          # list of chars currently in the editor
    cursor = 0         # cursor position (0 .. len(text))
    ops = []

    t = rng.randint(1, 120)

    for _ in range(t):
        valid = []
        if cursor > 0:
            valid.append('P')
        if cursor < len(text):
            valid.append('N')
        valid.append('M')
        valid.append('I')
        if cursor < len(text):
            valid.append('D')
            valid.append('G')

        choice = rng.choice(valid)

        if choice == 'P':
            ops.append("Prev")
            cursor -= 1
        elif choice == 'N':
            ops.append("Next")
            cursor += 1
        elif choice == 'M':
            k = rng.randint(0, len(text))
            ops.append(f"Move {k}")
            cursor = k
        elif choice == 'I':
            n = rng.randint(1, 20)
            s = ''.join(chr(rng.randint(32, 126)) for _ in range(n))
            text[cursor:cursor] = list(s)
            # cursor unchanged
            # Sometimes split the string across lines so the parser
            # must skip embedded newlines (per problem statement).
            if n > 1 and rng.random() < 0.3:
                split = rng.randint(1, n - 1)
                ops.append(f"Insert {n}\n{s[:split]}\n{s[split:]}")
            else:
                ops.append(f"Insert {n}\n{s}")
        elif choice == 'D':
            max_del = len(text) - cursor
            n = rng.randint(1, max_del)
            del text[cursor:cursor + n]
            ops.append(f"Delete {n}")
        elif choice == 'G':
            max_get = len(text) - cursor
            n = rng.randint(1, max_get)
            ops.append(f"Get {n}")

    out = [str(len(ops))]
    out.extend(ops)
    print("\n".join(out))


main()
