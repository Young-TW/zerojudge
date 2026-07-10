import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # 字母與標點（不含空白）
    punct = ".,:;!?-'\"()[]{}@#$%^&*+=/<>~`|\\"
    lower = "abcdefghijklmnopqrstuvwxyz"
    upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    letters = lower + upper

    mode = rng.randint(0, 6)

    if mode == 0:
        # 只有標點 -> 過濾後為空字串 -> 迴文 (邊界)
        n = rng.randint(1, 5)
        s = "".join(rng.choice(punct) for _ in range(n))

    elif mode == 1:
        # 單一字母 -> 迴文
        s = rng.choice(letters)

    elif mode == 2:
        # 全部相同字母（混合大小寫）-> 迴文
        n = rng.randint(1, 12)
        c = rng.choice(letters)
        s = "".join(rng.choice([c, c.upper(), c.lower()]) for _ in range(n))

    elif mode == 3:
        # 偶數次字母 -> 必為迴文
        k = rng.randint(1, 6)
        chars = []
        for _ in range(k):
            c = rng.choice(lower)
            chars.append(c)
            chars.append(c)
        rng.shuffle(chars)
        s = "".join(chars)

    elif mode == 4:
        # 恰一個奇數次字母 -> 迴文
        k = rng.randint(0, 5)
        chars = []
        for _ in range(k):
            c = rng.choice(lower)
            chars.append(c)
            chars.append(c)
        chars.append(rng.choice(lower))
        rng.shuffle(chars)
        s = "".join(chars)

    elif mode == 5:
        # 隨機字母（可能有多個奇數次 -> 不一定迴文）
        n = rng.randint(2, 10)
        s = "".join(rng.choice(letters) for _ in range(n))

    else:
        # 一般混合：字母＋標點＋大小寫
        n = rng.randint(1, 25)
        pool = letters + punct
        s = "".join(rng.choice(pool) for _ in range(n))

    # 有時在中間插入標點，確保非字母字元存在
    if s and rng.random() < 0.4:
        idx = rng.randint(0, len(s))
        s = s[:idx] + rng.choice(punct) + s[idx:]

    # 保證無空白
    s = s.replace(" ", "")
    print(s)


main()
