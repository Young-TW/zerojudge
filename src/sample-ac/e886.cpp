#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
    long long y;
    long long x1, x2;
    int type;
    bool operator<(const Event& o) const {
        if (y != o.y) return y < o.y;
        return type > o.type;
    }
};

vector<long long> Xs;
vector<int> cnt;
vector<long long> len;

void update(int node, int l, int r, int ql, int qr, int val) {
    if (ql > qr) return;
    if (ql <= l && r <= qr) {
        cnt[node] += val;
    } else {
        int mid = (l + r) / 2;
        if (ql <= mid) update(node * 2, l, mid, ql, qr, val);
        if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr, val);
    }
    if (cnt[node] > 0) {
        len[node] = Xs[r + 1] - Xs[l];
    } else {
        if (l == r) {
            len[node] = 0;
        } else {
            len[node] = len[node * 2] + len[node * 2 + 1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long L, D, R, U;
    vector<Event> events;
    while (cin >> L >> D >> R >> U) {
        if (L > R) swap(L, R);
        if (D > U) swap(D, U);
        events.push_back({D, L, R, 1});
        events.push_back({U, L, R, -1});
        Xs.push_back(L);
        Xs.push_back(R);
    }

    if (events.empty()) {
        cout << 0 << "\n";
        return 0;
    }

    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());

    int m = Xs.size();
    if (m <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    cnt.resize(4 * m);
    len.resize(4 * m);

    sort(events.begin(), events.end());

    long long total_area = 0;
    for (size_t i = 0; i < events.size(); ++i) {
        if (i > 0) {
            long long dy = events[i].y - events[i - 1].y;
            total_area += len[1] * dy;
        }
        int ix1 = lower_bound(Xs.begin(), Xs.end(), events[i].x1) - Xs.begin();
        int ix2 = lower_bound(Xs.begin(), Xs.end(), events[i].x2) - Xs.begin();
        update(1, 0, m - 2, ix1, ix2 - 1, events[i].type);
    }

    cout << total_area << "\n";

    return 0;
}
