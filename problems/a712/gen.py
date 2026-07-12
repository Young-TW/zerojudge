import sys
import random


# Valid letters for a712: A-Y excluding Q and Z (Z not in mapping, Q not in mapping).
# Per problem: A,B,C->2; D,E,F->3; G,H,I->4; J,K,L->5; M,N,O->6;
#              P,R,S->7; T,U,V->8; W,X,Y->9. No mapping for Q or Z.
VALID_LETTERS = "ABCDEFGHIJKLMNOPRSTUVWXY"


def random_token(rng):
    # Build a string with exactly 7 meaningful chars (digit or letter),
    # plus a random number of hyphens inserted anywhere (including ends).
    parts = []
    for _ in range(7):
        if rng.randint(0, 1) == 0:
            parts.append(str(rng.randint(0, 9)))
        else:
            parts.append(rng.choice(VALID_LETTERS))

    # Decide hyphen placement: choose number of hyphens 0..7, random positions
    # including before first and after last char.
    num_hyphens = rng.randint(0, 7)
    # Insert hyphens: we have 8 gaps (before, between, after)
    gaps = [[] for _ in range(8)]
    for _ in range(num_hyphens):
        g = rng.randint(0, 7)
        gaps[g].append("-")

    out = []
    out.extend(gaps[0])
    for i in range(7):
        out.append(parts[i])
        out.extend(gaps[i + 1])
    return "".join(out)


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep small so brute runs <1s. Vary to cover edges: 1, small, mid, plus
    # a "many duplicates" case to exercise the duplicate-output path.
    roll = rng.randint(0, 4)
    if roll == 0:
        n = 1  # boundary: single entry -> always No duplicates.
    elif roll == 1:
        n = rng.randint(2, 8)  # tiny
    elif roll == 2:
        n = rng.randint(20, 60)  # small
    elif roll == 3:
        n = rng.randint(100, 300)  # still well under 1s for brute
    else:
        # Force many collisions: small pool of underlying numbers.
        n = rng.randint(50, 200)

    lines = [str(n)]
    for _ in range(n):
        if roll == 4:
            # Bias toward a tiny pool so duplicates are likely.
            if rng.randint(0, 1) == 0:
                # Pick a fully random 7-digit numeric base from a small set.
                base = rng.choice(["0000000", "1111111", "8884567", "3101010", "4873279"])
                # Render it with random formatting (hyphens / as letters).
                chars = list(base)
                token_chars = []
                for ch in chars:
                    if rng.randint(0, 1) == 0:
                        token_chars.append(ch)
                    else:
                        # Map some digits back to letters of the same key.
                        d = ch
                        letters = {
                            "2": "ABC", "3": "DEF", "4": "GHI", "5": "JKL",
                            "6": "MNO", "7": "PRS", "8": "TUV", "9": "WXY",
                            "0": "0", "1": "1",
                        }[d]
                        token_chars.append(rng.choice(letters))
                # Insert random hyphens.
                num_hyphens = rng.randint(0, 7)
                gaps = [[] for _ in range(8)]
                for _ in range(num_hyphens):
                    gaps[rng.randint(0, 7)].append("-")
                out = list(gaps[0])
                for i in range(7):
                    out.append(token_chars[i])
                    out.extend(gaps[i + 1])
                lines.append("".join(out))
            else:
                lines.append(random_token(rng))
        else:
            lines.append(random_token(rng))

    sys.stdout.write("\n".join(lines) + "\n")


main()
