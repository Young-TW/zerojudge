#include <cstdio>
#include <cstdint>
#include <vector>
#include <array>
#include <algorithm>
#include <queue>
#include <set>

/* ---------- fast input ---------- */
static const int BUFSIZE = 1 << 20;
static char ibuf[BUFSIZE];
static size_t ipos = 0, ilen = 0;

inline bool refill() {
    ilen = fread(ibuf, 1, BUFSIZE, stdin);
    ipos = 0;
    return ilen > 0;
}
inline bool readUInt(uint32_t &out) {
    char c;
    do {
        if (ipos >= ilen) if (!refill()) return false;
        c = ibuf[ipos++];
    } while (c < '0' || c > '9');
    uint32_t v = 0;
    while (c >= '0' && c <= '9') {
        v = v * 10 + (c - '0');
        if (ipos >= ilen) {
            if (!refill()) break;
        }
        c = ibuf[ipos++];
    }
    out = v;
    return true;
}

/* ---------- cube rotations on index permutations ---------- */
using Perm = std::array<int,6>;

static Perm rotX(const Perm &a) {
    Perm b = a;
    b[0] = a[4];
    b[1] = a[0];
    b[3] = a[1];
    b[4] = a[3];
    b[2] = a[2];
    b[5] = a[5];
    return b;
}
static Perm rotY(const Perm &a) {
    Perm b = a;
    b[0] = a[5];
    b[2] = a[0];
    b[3] = a[2];
    b[5] = a[3];
    b[1] = a[1];
    b[4] = a[4];
    return b;
}
static Perm rotZ(const Perm &a) {
    Perm b = a;
    b[1] = a[5];
    b[2] = a[1];
    b[4] = a[2];
    b[5] = a[4];
    b[0] = a[0];
    b[3] = a[3];
    return b;
}

/* ---------- generate the 24 permutations ---------- */
static std::vector<Perm> generatePerms() {
    std::set<Perm> seen;
    std::queue<Perm> q;
    Perm id = {0,1,2,3,4,5};
    seen.insert(id);
    q.push(id);
    while (!q.empty()) {
        Perm cur = q.front(); q.pop();
        Perm nxt;
        nxt = rotX(cur);
        if (seen.insert(nxt).second) q.push(nxt);
        nxt = rotY(cur);
        if (seen.insert(nxt).second) q.push(nxt);
        nxt = rotZ(cur);
        if (seen.insert(nxt).second) q.push(nxt);
    }
    std::vector<Perm> res(seen.begin(), seen.end());   // size = 24
    return res;
}

/* ---------- main ---------- */
int main() {
    uint32_t n;
    if (!readUInt(n)) return 0;

    const std::vector<Perm> perms = generatePerms();   // 24 elements

    std::vector< std::array<uint32_t,6> > canonical;
    canonical.reserve(n);

    uint32_t v[6];
    for (uint32_t i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) readUInt(v[j]);

        std::array<uint32_t,6> best;
        bool first = true;

        for (const Perm &p : perms) {
            std::array<uint32_t,6> cur;
            for (int k = 0; k < 6; ++k) cur[k] = v[p[k]];
            if (first || cur < best) {
                best = cur;
                first = false;
            }
        }
        canonical.push_back(best);
    }

    std::sort(canonical.begin(), canonical.end());

    uint32_t distinct = 0;
    for (size_t i = 0; i < canonical.size(); ++i) {
        if (i == 0 || canonical[i] != canonical[i-1]) ++distinct;
    }

    printf("%u\n", distinct);
    return 0;
}
