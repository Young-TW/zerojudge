import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    n = rng.randint(2, 12)
    perm = list(range(1, n + 1))
    rng.shuffle(perm)
    print(n)
    print(' '.join(map(str, perm)))
    num_students = rng.randint(1, 5)
    for _ in range(num_students):
        if rng.random() < 0.2:
            stu = list(perm)
        else:
            stu = list(range(1, n + 1))
            rng.shuffle(stu)
        print(' '.join(map(str, stu)))


main()
