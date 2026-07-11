import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    # H >= 1, K >= 1, H + K <= 9
    H = rng.randint(1, 8)
    K = rng.randint(1, 9 - H)
    print(f"{H} {K}")
    print("0 0")

if __name__ == "__main__":
    main()
