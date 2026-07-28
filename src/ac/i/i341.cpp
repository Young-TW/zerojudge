#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

struct Query {
    long long C;
    int l, r;
};

struct BIT {
    int n;
    std::vector<int> tree;
    BIT(int sz) : n(sz), tree(sz + 1, 0) {}
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) tree[idx] += val;
    }
    int sum(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += tree[idx];
        return res;
    }
};

long long process_queries(std::vector<long long>& vals, std::vector<Query>& queries) {
    if (queries.empty()) return 0;
    int n = (int)vals.size() - 1;
    std::vector<std::pair<long long, int>> vec;
    vec.reserve(n);
    for (int i = 1; i <= n; ++i) {
        vec.push_back({vals[i], i});
    }
    std::sort(vec.begin(), vec.end());
    std::sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) { return a.C < b.C; });
    BIT bit(n);
    long long total = 0;
    int ptr = 0;
    for (auto& q : queries) {
        while (ptr < n && vec[ptr].first <= q.C) {
            bit.add(vec[ptr].second, 1);
            ++ptr;
        }
        total += bit.sum(q.r) - bit.sum(q.l - 1);
    }
    return total;
}

long long solve(int l, int r, std::vector<int>& P, int K) {
    if (l == r) return 1;
    int mid = (l + r) / 2;
    long long ans = solve(l, mid, P, K) + solve(mid+1, r, P, K);
    int lenR = r - mid;
    std::vector<int> rmax(lenR + 1), rmin(lenR + 1);
    std::vector<long long> A(lenR + 1), E(lenR + 1), D(lenR + 1);
    for (int i = 1; i <= lenR; ++i) {
        int R = mid + i;
        if (i == 1) {
            rmax[i] = rmin[i] = P[R];
        } else {
            rmax[i] = std::max(rmax[i-1], P[R]);
            rmin[i] = std::min(rmin[i-1], P[R]);
        }
        A[i] = (long long)rmax[i] - R;
        E[i] = (long long)-rmin[i] - R;
        D[i] = (long long)rmax[i] - rmin[i] - R;
    }
    std::vector<Query> q2, q3, q4;
    long long cross = 0;
    int pr_max = 1, pr_min = 1;
    int lmax, lmin;
    for (int L = mid; L >= l; --L) {
        if (L == mid) {
            lmax = lmin = P[mid];
        } else {
            lmax = std::max(lmax, P[L]);
            lmin = std::min(lmin, P[L]);
        }
        while (pr_max <= lenR && rmax[pr_max] <= lmax) ++pr_max;
        while (pr_min <= lenR && rmin[pr_min] >= lmin) ++pr_min;
        if (pr_max <= pr_min) {
            if (1 <= pr_max - 1) {
                long long C1 = (long long)lmax - lmin + L - K;
                long long need = C1 - mid;
                long long i_min = std::max(1LL, need);
                long long i_max = pr_max - 1;
                if (i_min <= i_max) cross += (i_max - i_min + 1);
            }
            if (pr_max <= pr_min - 1) {
                long long C2 = (long long)K - L + lmin;
                q2.push_back({C2, pr_max, pr_min - 1});
            }
            if (pr_min <= lenR) {
                long long C3 = (long long)K - L;
                q4.push_back({C3, pr_min, lenR});
            }
        } else {
            if (1 <= pr_min - 1) {
                long long C1 = (long long)lmax - lmin + L - K;
                long long need = C1 - mid;
                long long i_min = std::max(1LL, need);
                long long i_max = pr_min - 1;
                if (i_min <= i_max) cross += (i_max - i_min + 1);
            }
            if (pr_min <= pr_max - 1) {
                long long C4 = (long long)K - L - lmax;
                q3.push_back({C4, pr_min, pr_max - 1});
            }
            if (pr_max <= lenR) {
                long long C3 = (long long)K - L;
                q4.push_back({C3, pr_max, lenR});
            }
        }
    }
    cross += process_queries(A, q2);
    cross += process_queries(E, q3);
    cross += process_queries(D, q4);
    ans += cross;
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        int N, K;
        std::cin >> N >> K;
        std::vector<int> P(N+1);
        for (int i = 1; i <= N; ++i) std::cin >> P[i];
        long long ans = solve(1, N, P, K);
        std::cout << ans << '\n';
    }
    return 0;
}
