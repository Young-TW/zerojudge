import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    num_cases = rng.randint(1, 6)
    lines = []

    for _ in range(num_cases):
        r = rng.random()

        if r < 0.15:
            # 邊界：n=1，唯一追求者必為答案
            by, bm, bd = rng.randint(1, 9999), rng.randint(1, 12), rng.randint(1, 28)
            lines.append(f"{by} {bm} {bd}")
            lines.append("1")
            sy, sm, sd = rng.randint(1, 9999), rng.randint(1, 12), rng.randint(1, 28)
            lines.append(f"{sy} {sm} {sd}")

        elif r < 0.30:
            # 邊界：追求者全部跟正妹特別數完全相同，應輸出 1（先到先贏）
            by = rng.randint(1, 9999)
            bm = rng.randint(1, 12)
            bd = rng.randint(1, 28)
            lines.append(f"{by} {bm} {bd}")
            n = rng.randint(1, 40)
            lines.append(f"{n}")
            # 直接用同一個生日重複，特別數必定相同
            for _ in range(n):
                lines.append(f"{by} {bm} {bd}")

        elif r < 0.45:
            # 邊界：刻意湊出多個最相近者，考驗「先到先贏」
            # 正妹特別數固定為 1（用 1/1/1 -> 1+1+1=3 -> 3），追求者特別數都差 2
            lines.append("1 1 1")
            n = rng.randint(2, 40)
            lines.append(f"{n}")
            for _ in range(n):
                # 用 9/9/9 -> 9+9+9=27->9，跟 3 差 6；固定差值確保所有人都同等級
                lines.append("9 9 9")

        elif r < 0.58:
            # 邊界：涵蓋最小年(1)、最大年(9999)、最小與最大月日
            by = rng.choice([1, 9999])
            bm = rng.choice([1, 12])
            bd = rng.choice([1, 31])
            lines.append(f"{by} {bm} {bd}")
            n = rng.randint(1, 40)
            lines.append(f"{n}")
            for _ in range(n):
                yy = rng.choice([1, 9999, rng.randint(1, 9999)])
                mm = rng.choice([1, 12, rng.randint(1, 12)])
                dd = rng.choice([1, 31, rng.randint(1, 31)])
                lines.append(f"{yy} {mm} {dd}")

        elif r < 0.70:
            # 邊界：n 達上限 100，純粹測規模上限
            by, bm, bd = rng.randint(1, 9999), rng.randint(1, 12), rng.randint(1, 28)
            lines.append(f"{by} {bm} {bd}")
            lines.append("100")
            for _ in range(100):
                sy, sm, sd = rng.randint(1, 9999), rng.randint(1, 12), rng.randint(1, 28)
                lines.append(f"{sy} {sm} {sd}")

        else:
            # 一般隨機
            by, bm, bd = rng.randint(1, 9999), rng.randint(1, 12), rng.randint(1, 28)
            lines.append(f"{by} {bm} {bd}")
            n = rng.randint(1, 60)
            lines.append(f"{n}")
            for _ in range(n):
                sy, sm, sd = rng.randint(1, 9999), rng.randint(1, 12), rng.randint(1, 28)
                lines.append(f"{sy} {sm} {sd}")

    sys.stdout.write("\n".join(lines) + "\n")


main()
