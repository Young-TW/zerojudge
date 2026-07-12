import sys
from random import Random

def main():
    rng = Random(int(sys.argv[1]))
    # 25 non-negative integers, each <= 10.
    # Order: a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,x,y,z
    # n is the 14th value (index 13). Keep n small (1..6) so brute runs fast,
    # but cover boundaries: n=1,2,3 exercise the "referenced size < 1" guards.
    vals = [rng.randint(0, 10) for _ in range(25)]
    # Force n (index 13) into a small range covering boundaries 1..6.
    vals[13] = rng.randint(1, 6)
    # Occasionally force boundary n values.
    r = rng.randint(0, 9)
    if r == 0:
        vals[13] = 1
    elif r == 1:
        vals[13] = 2
    elif r == 2:
        vals[13] = 3
    # Occasionally force some multipliers/coefficient to 0 (boundary).
    if rng.randint(0, 4) == 0:
        for _ in range(rng.randint(1, 3)):
            vals[rng.randint(0, 12)] = 0   # one of a..n (excl n handled above)
        for _ in range(rng.randint(0, 2)):
            vals[rng.randint(14, 24)] = 0  # one of o..z
    print(" ".join(str(v) for v in vals))

if __name__ == "__main__":
    main()
