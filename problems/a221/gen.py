import sys
import random
import string


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Small scale: t in [1, 10] so brute is instant, but covers the boundary of
    # up to 20 words per line and all three verdicts.
    t = rng.randint(1, 10)
    out = [str(t)]

    for _ in range(t):
        verdict = rng.choice(["Yes", "OFE", "WA"])

        # 1..20 words per line (cover the stated max of 20).
        k = rng.randint(1, 20)
        words = []
        for _ in range(k):
            wlen = rng.randint(1, 8)
            w = "".join(rng.choice(string.ascii_letters) for _ in range(wlen))
            words.append(w)

        # Judge output has only words, no spaces.
        judge = "".join(words)

        if verdict == "Yes":
            # Team must be byte-identical to judge -> no spaces at all.
            team = judge

        elif verdict == "OFE":
            # Insert spaces between/around words so that removing them reproduces
            # judge, but team != judge. Cover leading / trailing / multi-spaces.
            parts = []
            for i, w in enumerate(words):
                if i > 0:
                    parts.append(" " * rng.randint(1, 4))
                parts.append(w)
            team = "".join(parts)
            if rng.random() < 0.5:
                team = (" " * rng.randint(1, 3)) + team
            if rng.random() < 0.5:
                team = team + (" " * rng.randint(1, 3))
            # k == 1 case: force at least one space so it is not accidentally "Yes".
            if " " not in team:
                team = " " + team
            assert team.replace(" ", "") == judge

        else:  # WA: content must genuinely differ after ignoring spaces.
            mode = rng.randint(0, 3)
            if mode == 0:
                # Flip case of a random character.
                lst = list(judge)
                idx = rng.randrange(len(lst))
                lst[idx] = lst[idx].swapcase()
                team = "".join(lst)
            elif mode == 1 and len(judge) > 1:
                # Drop one character.
                idx = rng.randrange(len(judge))
                team = judge[:idx] + judge[idx + 1:]
            elif mode == 2:
                # Prepend an extra word (with spaces) -> different content.
                extra = "".join(
                    rng.choice(string.ascii_letters)
                    for _ in range(rng.randint(1, 5))
                )
                team = (" " * rng.randint(1, 3)) + extra + (" " * rng.randint(1, 3)) + judge
            else:
                # Entirely unrelated string.
                team = "".join(
                    rng.choice(string.ascii_letters)
                    for _ in range(rng.randint(1, 10))
                )
            # Guarantee it is truly WA (never accidentally Yes or OFE), and that
            # the team line still carries at least one word.
            if team == judge or team.replace(" ", "") == judge:
                team = team + "x"
            if team.replace(" ", "") == "":
                team = "x"

        out.append(team)
        out.append(judge)

    sys.stdout.write("\n".join(out) + "\n")


main()
