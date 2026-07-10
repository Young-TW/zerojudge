#!/usr/bin/env python3
import sys
import random

def main():
    rnd = random.Random(int(sys.argv[1]))
    lines = []
    # Case 1: identical small strings
    alphabet = [chr(c) for c in range(33, 127)]
    s1 = "".join(rnd.choice(alphabet) for _ in range(rnd.randint(1, 8)))
    s2 = "".join(s1)
    lines.append((s1, s2))
    # Case 2: anagrams (permutation)
    n = rnd.randint(1, 10)
    s1 = "".join(rnd.choice(alphabet) for _ in range(n))
    perm = list(s1)
    rnd.shuffle(perm)
    s2 = "".join(perm)
    if s2 == s1:
        s2 = s2[::-1]  # ensure different order if possible
    lines.append((s1, s2))
    # Case 3: not anagrams (different length)
    s1 = "".join(rnd.choice(alphabet) for _ in range(rnd.randint(1, 8)))
    s2 = "".join(rnd.choice(alphabet) for _ in range(rnd.randint(1, 8)))
    lines.append((s1, s2))
    # Case 4: same length, random chars -> likely not anagram
    n = rnd.randint(1, 12)
    s1 = "".join(rnd.choice(alphabet) for _ in range(n))
    s2 = "".join(rnd.choice(alphabet) for _ in range(n))
    lines.append((s1, s2))
    # Case 5: single char identical
    c = rnd.choice(alphabet)
    lines.append((c, c))
    # Case 6: single char different
    c1 = rnd.choice(alphabet)
    c2 = rnd.choice(alphabet)
    while c2 == c1:
        c2 = rnd.choice(alphabet)
    lines.append((c1, c2))
    # Case 7: boundary chars 33 and 126
    lines.append(("!", "~"))
    lines.append(("!!", "~~"))
    lines.append(("!~", "~!"))
    for s1, s2 in lines:
        sys.stdout.write(s1 + "\n")
        sys.stdout.write(s2 + "\n")
    sys.stdout.write("STOP!!\n")

if __name__ == "__main__":
    main()
