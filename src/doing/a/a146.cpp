#include <deque>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    while (cin >> n >> k) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<int> mn, mx;
        // monotonic deque for minimum: increasing
        deque<int> dqMin, dqMax;
        for (int i = 0; i < n; ++i) {
            while (!dqMin.empty() && a[dqMin.back()] >= a[i]) dqMin.pop_back();
            dqMin.push_back(i);
            while (!dqMax.empty() && a[dqMax.back()] <= a[i]) dqMax.pop_back();
            dqMax.push_back(i);

            while (!dqMin.empty() && dqMin.front() <= i - k) dqMin.pop_front();
            while (!dqMax.empty() && dqMax.front() <= i - k) dqMax.pop_front();

            if (i >= k - 1) {
                mn.push_back(a[dqMin.front()]);
                mx.push_back(a[dqMax.front()]);
            }
        }

        for (size_t i = 0; i < mn.size(); ++i) {
            cout << mn[i];
            cout << (i + 1 == mn.size() ? '\n' : ' ');
        }
        for (size_t i = 0; i < mx.size(); ++i) {
            cout << mx[i];
            cout << (i + 1 == mx.size() ? '\n' : ' ');
        }
    }
    return 0;
}
