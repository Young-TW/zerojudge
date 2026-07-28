import sys, random

def main():
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    # ---- special seeds for corner cases ----
    if seed == 0:
        # minimal: only a query, no clouds
        n, length = 1, 0
        print(f"{n} {length}")
        print("2 0 0 0")
        return

    if seed == 1:
        # one cloud and one query covering it
        n, length = 2, 10
        print(f"{n} {length}")
        print("1 0 5 2 8 1")          # insert cloud color 5, [2,8], dir right, at t=0
        print("2 1 0 10")             # query at t=1, interval [0,10]
        return

    if seed == 2:
        # edge values, whole range cloud, point query, delete
        n, length = 5, 2000000000
        print(f"{n} {length}")
        print("1 0 1 0 2000000000 1")   # insert whole‑range cloud color 1
        print("2 1 0 2000000000")       # query whole range
        print("1 2 2 0 0 -1")           # insert point cloud color 2 at position 0
        print("2 3 0 0")                # query that point
        print("3 4 1")                  # delete color 1
        return

    # ---- general random test generation ----
    MAX_N = 200000
    MAX_LEN = 2000000000
    MAX_TIME_GAP = 10

    n = rnd.randint(1, MAX_N)
    length = rnd.randint(1, MAX_LEN)
    print(f"{n} {length}")

    active = {}          # color -> (Ti, Li, Ri, Di)
    next_color = 1
    current_time = 0

    for _ in range(n):
        # decide event type, but keep at least one insert if no active clouds
        if not active:
            typ = 1
        else:
            typ = rnd.choices([1, 2, 3], weights=[3, 5, 2])[0]

        if typ == 1:
            # insert event
            Ti = current_time + rnd.randint(0, MAX_TIME_GAP)
            color = next_color
            next_color += 1
            Li = rnd.randint(0, length)
            Ri = rnd.randint(Li, length)
            Di = rnd.choice([-1, 1])
            active[color] = (Ti, Li, Ri, Di)
            print(f"1 {Ti} {color} {Li} {Ri} {Di}")

        elif typ == 2:
            # query event
            Ti = current_time + rnd.randint(0, MAX_TIME_GAP)
            Li = rnd.randint(0, length)
            Ri = rnd.randint(Li, length)
            print(f"2 {Ti} {Li} {Ri}")

        else:  # typ == 3, delete event
            Ti = current_time + rnd.randint(0, MAX_TIME_GAP)
            color = rnd.choice(list(active.keys()))
            del active[color]
            print(f"3 {Ti} {color}")

        # advance base time a little to keep times roughly non‑decreasing
        current_time += rnd.randint(0, 5)

if __name__ == "__main__":
    main()
