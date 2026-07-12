#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check(int k, int n, int m, int c, vector<int>& p) {
    int head = 0;
    int ptr = 0;
    for (int r = 1; r <= n; ++r) {
        while (ptr < m && p[ptr] <= r + k) {
            ptr++;
        }
        for (int i = 0; i < c; ++i) {
            if (head >= ptr || p[head] < r - k) {
                return false;
            }
            head++;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while (cin >> n >> m) {
        vector<int> p(m);
        for (int i = 0; i < m; ++i) {
            cin >> p[i];
        }
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        sort(p.begin(), p.end());
        int c = m / n;
        int low = 0, high = n;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (check(mid, n, m, c, p)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        cout << low << "\n";
    }
    return 0;
}
