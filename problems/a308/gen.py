import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    lower = 'abcdefghijklmnopqrstuvwxyz'

    def rand_word(min_len=1, max_len=6):
        return ''.join(rng.choice(lower) for _ in range(rng.randint(min_len, max_len)))

    def rand_case_word(min_len=1, max_len=6):
        w = rand_word(min_len, max_len)
        return ''.join(c.upper() if rng.random() < 0.5 else c for c in w)

    scenario = rng.randint(0, 8)

    if scenario == 0:
        # General random: word may or may not appear (inserted randomly)
        word = rand_case_word()
        n = rng.randint(0, 10)
        words = [rand_case_word() for _ in range(n)]
        for _ in range(rng.randint(0, 3)):
            if n > 0:
                words.insert(rng.randint(0, len(words)), word)
        article = ' '.join(words)
    elif scenario == 1:
        # Word is a substring of another word (must NOT match)
        word = rand_word(2, 3)
        prefix = rand_word(1, 3)
        suffix = rand_word(1, 3)
        article = prefix + word + suffix
    elif scenario == 2:
        # Leading spaces before first word
        word = rand_case_word()
        spaces = ' ' * rng.randint(1, 5)
        article = spaces + word + ' ' + rand_case_word()
    elif scenario == 3:
        # Trailing spaces after last word
        word = rand_case_word()
        spaces = ' ' * rng.randint(1, 5)
        article = rand_case_word() + ' ' + word + spaces
    elif scenario == 4:
        # Multiple consecutive spaces between words
        word = rand_case_word()
        parts = [word, rand_case_word(), word, rand_case_word()]
        article = '  '.join(parts)
    elif scenario == 5:
        # Single-character word, mixed with other single-char words
        word = rng.choice(lower)
        pool = [word, word.upper(), rand_case_word(1, 1)]
        article = ' '.join(rng.choice(pool) for _ in range(rng.randint(1, 8)))
    elif scenario == 6:
        # Empty article (line 2 is blank)
        word = rand_case_word()
        article = ''
    elif scenario == 7:
        # Article is only spaces
        word = rand_case_word()
        article = ' ' * rng.randint(1, 10)
    else:
        # Word appears as both standalone and as substring of other words
        word = rand_case_word()
        w_lower = word.lower()
        embed = rand_word(1, 2) + w_lower + rand_word(1, 2)
        article = ' '.join([word, embed, word, embed, word])

    print(word)
    print(article)


main()
