import sys
import random

def gen_phrase(rng):
    length = rng.randint(1, 12)
    letters = [rng.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(length)]
    if length > 4 and rng.random() < 0.5:
        num_words = rng.randint(2, min(3, length))
        splits = sorted(rng.sample(range(1, length), num_words - 1))
        words = []
        prev = 0
        for s in splits:
            words.append(''.join(letters[prev:s]))
            prev = s
        words.append(''.join(letters[prev:]))
        return ' '.join(words)
    else:
        return ''.join(letters)

def make_anagram(rng, base):
    letters = [c for c in base if c != ' ']
    for _ in range(20):
        shuffled = letters[:]
        rng.shuffle(shuffled)
        num_spaces = base.count(' ')
        if num_spaces > 0 and len(shuffled) > num_spaces:
            splits = sorted(rng.sample(range(1, len(shuffled)), num_spaces))
            words = []
            prev = 0
            for s in splits:
                words.append(''.join(shuffled[prev:s]))
                prev = s
            words.append(''.join(shuffled[prev:]))
            result = ' '.join(words)
        else:
            result = ''.join(shuffled)
        if result != base:
            return result
    return result

def main():
    rng = random.Random(int(sys.argv[1]))
    
    T = rng.randint(1, 5)
    print(T)
    
    for _ in range(T):
        print()
        
        n = rng.randint(1, 25)
        lines = []
        
        for _ in range(n):
            if lines and rng.random() < 0.5:
                base = rng.choice(lines)
                anagram = make_anagram(rng, base)
                lines.append(anagram)
            else:
                lines.append(gen_phrase(rng))
        
        for line in lines:
            print(line)

main()
