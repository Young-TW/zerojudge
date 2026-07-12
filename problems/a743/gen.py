import sys
import random


# Pool of country names (single word, letters only, as the problem guarantees).
COUNTRIES = [
    "Spain", "England", "Italy", "Germany", "France",
    "Turkey", "Portugal", "Greece", "Russia", "Sweden",
    "Norway", "Brazil", "Mexico", "Canada", "Japan",
    "China", "India", "Egypt", "Iran", "Poland",
]

WOMEN_FIRST = [
    "Anna", "Jane", "Donna", "Elvira", "Maria",
    "Lucia", "Sofia", "Elena", "Clara", "Rosa",
    "Bianca", "Greta", "Ingrid", "Yuki", "Aisha",
]

WOMEN_LAST = [
    "Doe", "Elvira", "Smith", "Rossi", "Garcia",
    "Muller", "Dubois", "Khan", "Tanaka", "Singh",
    "Anders", "Olsen", "Costa", "Russo", "Ferro",
]


def rand_token(rng):
    # A name token: letter string, lengths 1..10, mixed case but starts
    # with uppercase. Keep it a single word (no spaces).
    L = rng.randint(1, 10)
    letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    s = rng.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
    for _ in range(L - 1):
        s += rng.choice(letters)
    return s


def gen_line(rng):
    # Country is the first word; the rest is the woman's name (>=1 word,
    # since the problem lists a name after the country). Total line length
    # must be <= 75 characters.
    country = rng.choice(COUNTRIES)
    # Build a name of 1..5 words, total length bounded by 75.
    max_words = rng.randint(1, 5)
    words = []
    total = len(country)
    while len(words) < max_words:
        roll = rng.randint(0, 2)
        if roll == 0:
            w = rng.choice(WOMEN_FIRST)
        elif roll == 1:
            w = rng.choice(WOMEN_LAST)
        else:
            w = rand_token(rng)
        # +1 for the separating space.
        if total + 1 + len(w) > 75:
            break
        words.append(w)
        total += 1 + len(w)
    # Guarantee at least one name word (problem always has a name).
    if not words:
        # Find any word that fits.
        w = rng.choice(WOMEN_FIRST)
        if len(country) + 1 + len(w) > 75:
            w = "A"  # absolute fallback to satisfy <=75 and >=1 word
        words.append(w)
    return country + " " + " ".join(words)


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep n small so brute (sort of n strings) runs well under 1s, but
    # cover boundaries: n minimal, small, mid, and a "all-same-country"
    # stress. Problem allows up to 2000 lines; we cap at ~2000 for one
    # boundary case but that is still trivial for a sort+count brute.
    roll = rng.randint(0, 5)
    if roll == 0:
        n = 1  # boundary: single conquest
    elif roll == 1:
        n = rng.randint(2, 8)  # tiny
    elif roll == 2:
        n = rng.randint(20, 80)  # small
    elif roll == 3:
        n = rng.randint(200, 600)  # mid
    elif roll == 4:
        n = rng.randint(1800, 2000)  # near-max boundary
    else:
        # All the same country to stress counting of one big bucket.
        n = rng.randint(100, 2000)

    forced_country = rng.choice(COUNTRIES)

    out = [str(n)]
    for _ in range(n):
        if roll == 5:
            # Force same country; vary the name.
            name_words = []
            total = len(forced_country)
            k = rng.randint(1, 4)
            for _ in range(k):
                w = rng.choice(WOMEN_FIRST + WOMEN_LAST)
                if total + 1 + len(w) > 75:
                    break
                name_words.append(w)
                total += 1 + len(w)
            if not name_words:
                name_words.append("A")
            out.append(forced_country + " " + " ".join(name_words))
        else:
            out.append(gen_line(rng))

    sys.stdout.write("\n".join(out) + "\n")


main()
