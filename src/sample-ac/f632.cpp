#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T1, T2, K, P;
    if (!(cin >> T1 >> T2 >> K >> P)) return 0;

    vector<pair<int, int>> passengers;
    int t, m;
    while (cin >> t >> m) {
        passengers.push_back({t, m});
    }

    sort(passengers.begin(), passengers.end());

    priority_queue<int> pq;
    size_t idx = 0;
    long long total_tip = 0;
    int total_passengers = 0;

    for (int S = T1; S <= T2; S += K) {
        while (idx < passengers.size() && passengers[idx].first <= S) {
            pq.push(passengers[idx].second);
            idx++;
        }
        for (int i = 0; i < P && !pq.empty(); ++i) {
            total_tip += pq.top();
            pq.pop();
            total_passengers++;
        }
    }

    cout << total_passengers << " " << total_tip << "\n";

    return 0;
}
