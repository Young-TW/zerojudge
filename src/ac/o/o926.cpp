#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<pair<long long, long long>> buildings(N);
    long long global_max_h = 0;

    for (int i = 0; i < N; ++i) {
        int K;
        cin >> K;
        long long local_max_h = 0;
        for (int j = 0; j < K; ++j) {
            long long h;
            cin >> h;
            if (h > local_max_h) {
                local_max_h = h;
            }
        }
        buildings[i] = {K, local_max_h};
        if (local_max_h > global_max_h) {
            global_max_h = local_max_h;
        }
    }

    long long total_blocks = 0;
    for (int i = 0; i < N; ++i) {
        total_blocks += buildings[i].first * (global_max_h - buildings[i].second);
    }

    cout << total_blocks << "\n";

    return 0;
}
