#!/usr/bin/env python3
import sys
from random import Random

def main():
    seed = int(sys.argv[1])
    rng = Random(seed)

    # small scale so brute finishes within 1s
    N = rng.randint(1, 30)
    out = []
    out.append(str(N))

    par = [0] * (N + 1)
    par[1] = 0
    for i in range(2, N + 1):
        par[i] = rng.randint(1, i - 1)

    w = [0] * (N + 1)
    for i in range(1, N + 1):
        w[i] = rng.randint(0, 10000)

    for i in range(1, N + 1):
        out.append(f"{par[i]} {w[i]}")

    Q = rng.randint(1, 50)
    out.append(str(Q))

    for _ in range(Q):
        t = rng.randint(1, 3)
        if t == 1:
            x = rng.randint(1, N)
            y = rng.randint(1, N)
            out.append(f"1 {x} {y}")
        elif t == 2:
            x = rng.randint(1, N)
            val = rng.randint(0, 10000)
            out.append(f"2 {x} {val}")
        else:
            # change parent: pick x != 1, y must not create cycle
            x = rng.randint(2, N)
            # candidate y: any node in 1..N except descendants of x (to keep tree)
            # collect descendants of x
            desc = set()
            stack = [x]
            while stack:
                u = stack.pop()
                desc.add(u)
                for v in range(1, N + 1):
                    if v != u and par[v] == u and v not in desc:
                        stack.append(v)
            cand = [y for y in range(1, N + 1) if y not in desc]
            if not cand:
                # fallback to type 2 query instead
                xx = rng.randint(1, N)
                vv = rng.randint(0, 10000)
                out.append(f"2 {xx} {vv}")
            else:
                y = rng.choice(cand)
                par[x] = y
                out.append(f"3 {x} {y}")

    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()
