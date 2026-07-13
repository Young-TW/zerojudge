#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    vector<int> t(N);
    for (int i = 0; i < N; ++i) {
        cin >> t[i];
    }

    vector<pair<int, int>> lamps;
    for (int i = 0; i < N; ++i) {
        if (a[i] == -1) {
            lamps.emplace_back(0, t[i]);
        } else {
            lamps.emplace_back(a[i], t[i]);
        }
    }

    sort(lamps.begin(), lamps.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
        return x.first + x.second < y.first + y.second;
    });

    priority_queue<int, vector<int>, greater<int>> pq;
    int max_count = 0;
    long long current_time = 0;

    for (const auto& lamp : lamps) {
        int start = lamp.first;
        int duration = lamp.second;
        int end = start + duration;

        if (start > current_time) {
            current_time = start;
        }

        pq.push(duration);
        current_time += 1;

        while (!pq.empty() && current_time > end) {
            int min_duration = pq.top();
            pq.pop();
            current_time -= 1;
            if (current_time + min_duration > end) {
                pq.push(min_duration);
                break;
            }
        }

        if (pq.size() > max_count) {
            max_count = pq.size();
        }
    }

    cout << max_count << '\n';

    return 0;
}
