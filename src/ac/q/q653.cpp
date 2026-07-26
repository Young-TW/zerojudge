#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<pair<long long, long long>> a;
        a.reserve(N);
        for (int i = 0; i < N; ++i) {
            long long L, W;
            cin >> L >> W;
            a.emplace_back(L, W);
        }

        sort(a.begin(), a.end(),
            [](const pair<long long, long long>& p1,
               const pair<long long, long long>& p2) {
                if (p1.first != p2.first) return p1.first < p2.first;
                return p1.second > p2.second;          // descending W when L equal
            });

        vector<long long> tail;   // LIS on widths
        for (const auto& pr : a) {
            long long w = pr.second;
            auto it = lower_bound(tail.begin(), tail.end(), w);
            if (it == tail.end())
                tail.push_back(w);
            else
                *it = w;
        }

        cout << tail.size() << '\n';
    }
    return 0;
}
