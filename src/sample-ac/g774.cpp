#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        int K = N + M;
        vector<int> diff(K);
        long long total = 0;
        for (int i = 0; i < K; ++i) {
            int B, G;
            cin >> B >> G;
            total += G;
            diff[i] = B - G;
        }
        sort(diff.begin(), diff.end());
        for (int i = 0; i < N; ++i) {
            total += diff[i];
        }
        cout << total << "\n";
    }
    return 0;
}
