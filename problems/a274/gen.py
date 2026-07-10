import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # 測資筆數: 取小, 讓暴力 next_permutation 1 秒內跑完
    # (N<=10, 10! = 3628800, 但題目要字典序最小所以第一個找到即停)
    num_cases = rng.randint(1, 6)
    lines = []

    for _ in range(num_cases):
        # N: 1..10, 偏小以利暴力; 偶爾邊界
        r = rng.random()
        if r < 0.20:
            N = rng.choice([1, 2, 3])          # 極小 / 邊界
        elif r < 0.35:
            N = rng.choice([9, 10])            # 最大邊界
        else:
            N = rng.randint(1, 8)

        A = []
        for _ in range(N):
            r = rng.random()
            if r < 0.15:
                v = rng.choice([1, 2, 3])      # 小值: 容易整除 (容易有解)
            elif r < 0.30:
                v = rng.choice([9999999, 10000000, 4999999])  # 大值邊界
            elif r < 0.45:
                v = 1                          # 1 永遠整除 (測字典序/重複)
            else:
                v = rng.randint(1, 30)         # 中等值
            A.append(v)

        lines.append(str(N))
        lines.append(" ".join(map(str, A)))

    sys.stdout.write("\n".join(lines) + "\n")


main()
