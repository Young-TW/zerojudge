#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

int find(vector<int>& parent, int i) {
    while (parent[i] != i) {
        parent[i] = parent[parent[i]];
        i = parent[i];
    }
    return i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        while (T--) {
            int N, M;
            cin >> N >> M;
            vector<int> A(N + 1);
            for (int i = 1; i <= N; ++i) {
                cin >> A[i];
            }
            
            vector<int> parent(N + 1);
            vector<map<int, long long>> cnt(N + 1);
            
            for (int i = 1; i <= N; ++i) {
                parent[i] = i;
                cnt[i][A[i]] = 1;
            }
            
            long long total_stable_pairs = 0;
            
            for (int i = 0; i < M; ++i) {
                int x, y;
                cin >> x >> y;
                int rx = find(parent, x);
                int ry = find(parent, y);
                
                if (rx != ry) {
                    if (cnt[rx].size() < cnt[ry].size()) {
                        swap(rx, ry);
                    }
                    
                    for (auto& p : cnt[ry]) {
                        total_stable_pairs += cnt[rx][p.first] * p.second;
                        cnt[rx][p.first] += p.second;
                    }
                    
                    cnt[ry].clear();
                    parent[ry] = rx;
                }
                
                cout << total_stable_pairs << "\n";
            }
        }
    }
    
    return 0;
}
