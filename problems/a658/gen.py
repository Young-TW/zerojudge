import sys
import random

# Generator for a658 (NOI2012 骑行川藏).
# python3 a658_gen.py <seed>  -> prints one legal random input to stdout.
# Small scale so brute force finishes in <1s, but covers boundaries:
#   - N from 1 to 5
#   - s_i, k_i positive (lengths / wind coefficients)
#   - v'_i can be positive (tailwind), zero, or negative (headwind)
#   - EU ranges so that the problem is feasible and non-trivial
# Feasibility: minimum energy = sum over segments with v'<=0 of k_i*v'^2*s_i
#   (ride at wind speed when tailwind -> 0 energy; crawl at v->0 when headwind).
# We pick EU in [baseE*1.05, baseE*50] (or baseE + small if baseE==0) to stay feasible
# but sometimes near the boundary.

def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    rng = random.Random(seed)

    n = rng.randint(1, 5)
    segs = []
    baseE = 0.0
    for _ in range(n):
        s_i = rng.randint(1, 50000)            # length, positive
        k_i = rng.randint(1, 20)               # wind coefficient, positive
        # wind speed: mix of tailwind, zero, headwind
        r = rng.random()
        if r < 0.4:
            vp_i = rng.randint(1, 15)          # tailwind (positive)
        elif r < 0.6:
            vp_i = 0                           # no wind
        else:
            vp_i = -rng.randint(1, 15)         # headwind (negative)
        segs.append((s_i, k_i, vp_i))
        if vp_i <= 0:
            baseE += k_i * vp_i * vp_i * s_i

    if baseE < 1e-6:
        # all tailwind: min energy ~0; pick EU small-but-positive so constraint binds
        eu = rng.uniform(1.0, 100000.0)
    else:
        # feasible EU above baseline; sometimes just barely feasible
        eu = baseE * rng.uniform(1.02, 50.0)

    out = []
    out.append("%d %.8f" % (n, eu))
    for (s_i, k_i, vp_i) in segs:
        out.append("%d %d %d" % (s_i, k_i, vp_i))
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()
