import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    num_cases = rng.randint(1, 5)
    lines = []

    for _ in range(num_cases):
        # n: 0<n<=8; 偏邊界，但刻意取小讓暴力秒殺
        r = rng.random()
        if r < 0.20:
            n = rng.choice([1, 1, 2])          # 最小邊界
        elif r < 0.40:
            n = rng.choice([7, 8])             # 上界附近
        else:
            n = rng.randint(1, 6)              # 一般隨機

        m = 2 * n
        # 產生對稱好感度矩陣；對角線 0；含正數、零、負數
        mat = [[0] * m for _ in range(m)]
        for i in range(m):
            for j in range(i + 1, m):
                rv = rng.random()
                if rv < 0.15:
                    v = 0                          # 互不在乎
                elif rv < 0.35:
                    v = rng.randint(-50, -1)       # 互相憎恨 (賠償)
                else:
                    v = rng.randint(1, 50)         # 正向好感
                mat[i][j] = v
                mat[j][i] = v

        lines.append(str(n))
        for i in range(m):
            lines.append(" ".join(str(mat[i][j]) for j in range(m)))

    sys.stdout.write("\n".join(lines) + "\n")


main()
