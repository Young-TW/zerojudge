import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # 測資筆數: 取小, 讓暴力 1 秒內跑完
    num_cases = rng.randint(1, 8)
    lines = [str(num_cases)]

    for _ in range(num_cases):
        # x, y, z, w, n: 1..30 之間, 偶爾邊界 1 或大值
        def param():
            r = rng.random()
            if r < 0.20:
                return rng.choice([1, 2, 30, 50])
            return rng.randint(1, 30)

        x = param()
        y = param()
        z = param()
        w = param()
        n = param()

        # m: 初始體重, 多樣化: 含 1 (極易死), 小值, 大值
        r = rng.random()
        if r < 0.15:
            m = rng.choice([1, 2, 3])
        elif r < 0.30:
            m = rng.choice([10, 20, 50])
        else:
            m = rng.randint(1, 300)

        lines.append(f"{x} {y} {z} {w} {n} {m}")

        # 食物序列長度: 0 (空行) .. 25, 偏小
        r = rng.random()
        if r < 0.15:
            length = 0  # 沒吃 -> 直接輸出初始體重
        elif r < 0.30:
            length = rng.choice([1, 2])
        else:
            length = rng.randint(1, 25)

        food = []
        for _ in range(length):
            r = rng.random()
            if r < 0.15:
                food.append(0)        # 沒吃
            elif r < 0.40:
                food.append(4)        # 發霉, 累積中毒 (測毒性)
            elif r < 0.65:
                food.append(1)        # 紅
            elif r < 0.85:
                food.append(2)        # 白
            else:
                food.append(3)        # 黃

        if length == 0:
            lines.append("")          # 空行: 沒吃
        else:
            lines.append(" ".join(map(str, food)))

    sys.stdout.write("\n".join(lines) + "\n")


main()
