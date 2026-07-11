import sys
import random

def gen_string(rng, min_len=1, max_len=5):
    length = rng.randint(min_len, max_len)
    chars = 'abcde'
    return ''.join(rng.choice(chars) for _ in range(length))

def main():
    if len(sys.argv) < 2:
        sys.exit(1)
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    A = gen_string(rng)
    B = gen_string(rng)
    
    num_rules = rng.randint(1, 6)
    rules = []
    for _ in range(num_rules):
        a_rule = gen_string(rng)
        b_rule = gen_string(rng)
        rules.append((a_rule, b_rule))
        
    print(f"{A} {B}")
    for a_rule, b_rule in rules:
        print(f"{a_rule} {b_rule}")

if __name__ == "__main__":
    main()
