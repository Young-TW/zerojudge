#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Circle {
    long long L, R;
};

bool cmp(const Circle& a, const Circle& b) {
    if (a.L != b.L) return a.L < b.L;
    return a.R < b.R;
}

class BIT {
    vector<int> tree;
    int n;
public:
    BIT(int n) : n(n), tree(n + 1, 0) {}
    void update(int i, int delta) {
        for (; i <= n; i += i & (-i))
            tree[i] += delta;
    }
    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & (-i))
            sum += tree[i];
        return sum;
    }
    long long query_range(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<Circle> circles(n);
        vector<long long> vals;
        vals.reserve(2 * n);
        for (int i = 0; i < n; ++i) {
            long long x, r;
            cin >> x >> r;
            circles[i].L = x - r;
            circles[i].R = x + r;
            vals.push_back(circles[i].L);
            vals.push_back(circles[i].R);
        }
        sort(circles.begin(), circles.end(), cmp);
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        
        int m = vals.size();
        BIT bit(m);
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            int l_idx = lower_bound(vals.begin(), vals.end(), circles[i].L) - vals.begin() + 1;
            int r_idx = lower_bound(vals.begin(), vals.end(), circles[i].R) - vals.begin() + 1;
            long long cnt = bit.query_range(l_idx, r_idx);
            ans += i - cnt;
            bit.update(r_idx, 1);
        }
        cout << ans << "\n";
    }
    return 0;
}
