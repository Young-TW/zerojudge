import sys, random

def check_board(cols):
    # vertical check
    for col in cols:
        for i in range(len(col) - 2):
            if col[i] == col[i+1] == col[i+2]:
                return False
    # horizontal check
    for row in range(7):
        # collect colors present at this row
        row_colors = []
        for col in cols:
            if row < len(col):
                row_colors.append(col[row])
            else:
                row_colors.append(None)
        for i in range(5 - 2):
            c1, c2, c3 = row_colors[i], row_colors[i+1], row_colors[i+2]
            if c1 is not None and c1 == c2 == c3:
                return False
    return True

def generate_random_board(rng):
    while True:
        cols = []
        for _ in range(5):
            h = rng.randint(0, 7)
            col = [rng.randint(1, 10) for _ in range(h)]
            cols.append(col)
        if check_board(cols):
            return cols

def main():
    if len(sys.argv) != 2:
        return
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # step count n (positive)
    if seed == 0:
        n = 1
        cols = [[] for _ in range(5)]                     # empty board
    elif seed == 1:
        n = 1
        cols = [[1]] + [[] for _ in range(4)]            # single block at (0,0)
    elif seed == 2:
        n = 10
        cols = []
        for c in range(5):
            col = []
            for r in range(7):
                col.append(((r + c) % 10) + 1)            # deterministic pattern, no triples
            cols.append(col)
    else:
        n = rng.randint(1, 20)
        cols = generate_random_board(rng)

    # output
    out_lines = [str(n)]
    for col in cols:
        if col:
            out_lines.append(' '.join(map(str, col)) + ' 0')
        else:
            out_lines.append('0')
    sys.stdout.write('\n'.join(out_lines))

if __name__ == "__main__":
    main()
