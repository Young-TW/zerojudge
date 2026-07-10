import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # 測資筆數: 取小, 讓暴力 2^n 枚舉 1 秒內跑完
    num_cases = rng.randint(1, 6)
    lines = []

    for _ in range(num_cases):
        # N: 1..20, 偏小以利暴力 (2^N); 偶爾測邊界
        r = rng.random()
        if r < 0.20:
            N = rng.choice([1, 2, 3])          # 極小 / 邊界
        elif r < 0.40:
            N = rng.choice([18, 19, 20])       # 最大邊界
        else:
            N = rng.randint(1, 16)

        A = []
        for _ in range(N):
            r = rng.random()
            if r < 0.15:
                v = rng.choice([1, 2, 3])      # 小值: 容易湊出差 0
            elif r < 0.30:
                v = rng.choice([1, 1000000])   # 極值邊界
            elif r < 0.45:
                v = 1                          # 全 1: N 偶差 0, N 奇差 1
            else:
                v = rng.randint(1, 20)         # 中等值
            A.append(v)

        lines.append(str(N))
        lines.append(" ".join(map(str, A)))

    sys.stdout.write("\n".join(lines) + "\n")


main()
