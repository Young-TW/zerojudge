#include <bits/stdc++.h>
using namespace std;

struct Point {
    int idx;
    int x, y, z;
};

int N;
vector<Point> a;
vector<Point> tmp;
vector<int> bit;
vector<int> ans;

void bit_add(int idx, int val) {
    for (; idx <= N; idx += idx & -idx) bit[idx] += val;
}
int bit_query(int idx) {
    int res = 0;
    for (; idx > 0; idx -= idx & -idx) res += bit[idx];
    return res;
}

void cdq(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);

    // Count contributions from left half to right half
    int left_ptr = l;
    for (int right_ptr = mid + 1; right_ptr <= r; ++right_ptr) {
        while (left_ptr <= mid && a[left_ptr].y < a[right_ptr].y) {
            bit_add(a[left_ptr].z, 1);
            ++left_ptr;
        }
        ans[a[right_ptr].idx] += bit_query(a[right_ptr].z - 1);
    }
    // Clear BIT
    for (int i = l; i < left_ptr; ++i) {
        bit_add(a[i].z, -1);
    }

    // Merge the two halves by y ascending
    int p1 = l, p2 = mid + 1, p = l;
    while (p1 <= mid && p2 <= r) {
        if (a[p1].y <= a[p2].y) {
            tmp[p++] = a[p1++];
        } else {
            tmp[p++] = a[p2++];
        }
    }
    while (p1 <= mid) tmp[p++] = a[p1++];
    while (p2 <= r) tmp[p++] = a[p2++];
    for (int i = l; i <= r; ++i) a[i] = tmp[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N) {
        a.resize(N);
        tmp.resize(N);
        ans.assign(N, 0);
        bit.assign(N + 2, 0);

        for (int i = 0; i < N; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            // Transform to strict less problem
            a[i] = {i, N + 1 - x, N + 1 - y, N + 1 - z};
        }

        // Sort by x ascending, then y descending, then z descending
        sort(a.begin(), a.end(), [](const Point& p1, const Point& p2) {
            if (p1.x != p2.x) return p1.x < p2.x;
            if (p1.y != p2.y) return p1.y > p2.y;
            return p1.z > p2.z;
        });

        cdq(0, N - 1);

        for (int i = 0; i < N; ++i) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}
