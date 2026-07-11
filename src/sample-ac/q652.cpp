#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, K;
    while (cin >> N >> M >> K) {
        vector<int> A(N);
        unordered_map<int, vector<int>> posMap;
        posMap.reserve(N * 2);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            posMap[A[i]].push_back(i);
        }
        
        for (int q = 0; q < M; ++q) {
            bool impossible = false;
            long long pos = 0;
            for (int j = 0; j < K; ++j) {
                int v;
                cin >> v;
                if (impossible) continue;
                auto it = posMap.find(v);
                if (it == posMap.end()) {
                    impossible = true;
                    continue;
                }
                const vector<int>& vec = it->second;
                long long cycle = pos / N;
                int offset = pos % N;
                auto lb = lower_bound(vec.begin(), vec.end(), offset);
                if (lb != vec.end()) {
                    pos = cycle * N + (*lb) + 1;
                } else {
                    pos = (cycle + 1) * N + vec[0] + 1;
                }
            }
            if (impossible) {
                cout << -1 << '\n';
            } else {
                cout << pos << '\n';
            }
        }
    }
    return 0;
}
