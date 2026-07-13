#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, M;
    while (cin >> N >> M) {
        vector<long long> pos(N);
        for (long long i = 0; i < N; ++i) {
            cin >> pos[i];
        }
        sort(pos.begin(), pos.end());
        long long total_distance = 0;
        for (long long i = N - 1; i >= 0; i -= M) {
            total_distance += 2 * pos[i];
        }
        cout << total_distance / 8 << '\n';
    }
    return 0;
}
