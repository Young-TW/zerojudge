#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <numeric>
using namespace std;

static const int MAXN = 200010;

int N;
int Sarr[MAXN];
int sa[MAXN], rnk[MAXN], tmpsa[MAXN], lcptab[MAXN];
int sp[19][MAXN];
int lg2val[MAXN + 1];

vector<int> mst[4 * MAXN];

void buildSA() {
    int m = 0;
    for (int i = 0; i < N; i++) m = max(m, Sarr[i]);
    m++;
    static int cnt[MAXN];
    fill(cnt, cnt + m, 0);
    for (int i = 0; i < N; i++) cnt[Sarr[i]]++;
    for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    for (int i = N - 1; i >= 0; i--) sa[--cnt[Sarr[i]]] = i;

    rnk[sa[0]] = 0;
    for (int i = 1; i < N; i++) rnk[sa[i]] = rnk[sa[i-1]] + (Sarr[sa[i]] != Sarr[sa[i-1]]);

    for (int k = 1; rnk[sa[N-1]] < N - 1; k <<= 1) {
        int p = 0;
        for (int i = N - k; i < N; i++) tmpsa[p++] = i;
        for (int i = 0; i < N; i++) if (sa[i] >= k) tmpsa[p++] = sa[i] - k;

        int maxr = rnk[sa[N-1]] + 1;
        fill(cnt, cnt + maxr, 0);
        for (int i = 0; i < N; i++) cnt[rnk[i]]++;
        for (int i = 1; i < maxr; i++) cnt[i] += cnt[i - 1];
        for (int i = N - 1; i >= 0; i--) sa[--cnt[rnk[tmpsa[i]]]] = tmpsa[i];

        tmpsa[sa[0]] = 0;
        for (int i = 1; i < N; i++) {
            int cur = sa[i], prev = sa[i-1];
            int c1 = (cur + k < N) ? rnk[cur + k] : -1;
            int c2 = (prev + k < N) ? rnk[prev + k] : -1;
            tmpsa[sa[i]] = tmpsa[sa[i-1]] + (rnk[cur] != rnk[prev] || c1 != c2);
        }
        for (int i = 0; i < N; i++) rnk[i] = tmpsa[i];
    }
}

void buildLCP() {
    lcptab[0] = 0;
    int h = 0;
    for (int i = 0; i < N; i++) {
        if (rnk[i] > 0) {
            int j = sa[rnk[i] - 1];
            while (i + h < N && j + h < N && Sarr[i + h] == Sarr[j + h]) h++;
            lcptab[rnk[i]] = h;
            if (h > 0) h--;
        } else {
            h = 0;
        }
    }
}

void buildSparse() {
    lg2val[0] = -1;
    for (int i = 1; i <= N; i++) lg2val[i] = lg2val[i/2] + 1;
    for (int i = 0; i < N; i++) sp[0][i] = lcptab[i];
    for (int j = 1; (1 << j) <= N; j++)
        for (int i = 0; i + (1 << j) - 1 < N; i++)
            sp[j][i] = min(sp[j-1][i], sp[j-1][i + (1 << (j-1))]);
}

int lcpq(int l, int r) {
    if (l > r) return 0x3f3f3f3f;
    int k = lg2val[r - l + 1];
    return min(sp[k][l], sp[k][r - (1 << k) + 1]);
}

void buildMST(int node, int l, int r) {
    if (l == r) { mst[node].push_back(sa[l]); return; }
    int mid = (l + r) / 2;
    buildMST(2*node, l, mid);
    buildMST(2*node+1, mid+1, r);
    mst[node].resize(mst[2*node].size() + mst[2*node+1].size());
    merge(mst[2*node].begin(), mst[2*node].end(),
          mst[2*node+1].begin(), mst[2*node+1].end(),
          mst[node].begin());
}

int queryMST(int node, int l, int r, int ql, int qr, int lo, int hi) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) {
        return (int)(upper_bound(mst[node].begin(), mst[node].end(), hi) -
                     lower_bound(mst[node].begin(), mst[node].end(), lo));
    }
    int mid = (l + r) / 2;
    return queryMST(2*node, l, mid, ql, qr, lo, hi) +
           queryMST(2*node+1, mid+1, r, ql, qr, lo, hi);
}

void clearMST(int node, int l, int r) {
    if (mst[node].empty()) return;
    mst[node].clear();
    if (l == r) return;
    int mid = (l + r) / 2;
    clearMST(2*node, l, mid);
    clearMST(2*node+1, mid+1, r);
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        vector<long long> h(n + 1);
        for (int i = 1; i <= n; i++) scanf("%lld", &h[i]);

        int m = n - 1;

        if (m == 0) {
            int q;
            scanf("%d", &q);
            while (q--) {
                int l, r;
                scanf("%d %d", &l, &r);
                printf("0\n");
            }
            continue;
        }

        vector<long long> G(m);
        for (int i = 0; i < m; i++) G[i] = h[i+2] - h[i+1];

        vector<long long> vals;
        for (int i = 0; i < m; i++) {
            vals.push_back(G[i]);
            vals.push_back(-G[i]);
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        auto compress = [&](long long v) -> int {
            return (int)(lower_bound(vals.begin(), vals.end(), v) - vals.begin()) + 2;
        };

        N = 0;
        for (int i = 0; i < m; i++) Sarr[N++] = compress(G[i]);
        Sarr[N++] = 0;
        int negStart = N;
        for (int i = 0; i < m; i++) Sarr[N++] = compress(-G[i]);

        buildSA();
        buildLCP();
        buildSparse();
        buildMST(1, 0, N - 1);

        int q;
        scanf("%d", &q);
        while (q--) {
            int l, r;
            scanf("%d %d", &l, &r);
            int w = r - l + 1;
            if (w == 1) {
                printf("%d\n", n - 1);
                continue;
            }
            int gpos = l - 1;
            int qlen = w - 1;

            int g_rank = rnk[gpos];
            int low = g_rank, high = g_rank;
            {
                int L = 0, R = g_rank - 1;
                while (L <= R) {
                    int mid = (L + R) / 2;
                    if (lcpq(mid + 1, g_rank) >= qlen) { low = mid; R = mid - 1; }
                    else L = mid + 1;
                }
                L = g_rank + 1; R = N - 1;
                while (L <= R) {
                    int mid = (L + R) / 2;
                    if (lcpq(g_rank + 1, mid) >= qlen) { high = mid; L = mid + 1; }
                    else R = mid - 1;
                }
            }

            int ans = 0;
            int left_end = 2 * l - r - 2;
            int right_start = r;

            if (left_end >= 0) {
                ans += queryMST(1, 0, N - 1, low, high, negStart, negStart + left_end);
            }
            if (right_start <= m - 1) {
                ans += queryMST(1, 0, N - 1, low, high, negStart + right_start, negStart + m - 1);
            }

            printf("%d\n", ans);
        }

        clearMST(1, 0, max(N - 1, 1));
    }
    return 0;
}
