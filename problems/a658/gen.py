#!/usr/bin/env python3
import sys, random

def fmt(x):
    # ensure enough precision for judges
    return ("{:.10f}".format(x)).rstrip('0').rstrip('.') if '.' in "{:.10f}".format(x) else str(x)

def main():
    if len(sys.argv) != 2:
        return
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    # ----- corner cases for small seeds -----
    if seed == 0:
        # empty set of segments, zero energy
        N = 0
        EU = 0.0
        segs = []
    elif seed == 1:
        # single segment with extreme large values
        N = 1
        EU = 1e12
        segs = [(1e9, 1e6, 1e6)]
    elif seed == 2:
        # several identical moderate segments
        N = 5
        EU = 1e6
        segs = [(1000.0, 10.0, 5.0) for _ in range(N)]
    else:
        # ----- general random case -----
        # reasonable limits (can be tuned)
        max_N = 20000
        N = rnd.randint(1, max_N)
        EU = rnd.uniform(1e3, 1e9)

        segs = []
        for _ in range(N):
            s = rnd.uniform(1.0, 1e5)          # length
            k = rnd.uniform(0.1, 100.0)        # wind resistance coefficient
            v = rnd.uniform(-50.0, 50.0)       # wind speed (can be negative)
            segs.append((s, k, v))

    # ----- output -----
    out_lines = []
    out_lines.append(f"{N} {fmt(EU)}")
    for s, k, v in segs:
        out_lines.append(f"{fmt(s)} {fmt(k)} {fmt(v)}")
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()
