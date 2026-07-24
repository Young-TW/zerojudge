#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int solve() {
    int N;
    if (!(cin >> N)) return -1; // 結束標誌

    map<pair<int, int>, int> counts;
    
    for (int i = 0; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        counts[{u, v}]++;
    }

    int max_matches = 0;
    
    // 用來記錄已經處理過的配對，避免重複計算
    // 我們只處理 u <= v 的情況
    
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        int u = it->first.first;
        int v = it->first.second;
        
        // 只處理 u <= v 的情況
        if (u > v) continue;
        
        if (u == v) {
            // 自己配對自己
            max_matches += it->second / 2;
        } else {
            // u < v，檢查是否有反向的 v->u
            int count_uv = it->second;
            int count_vu = counts.count({v, u}) ? counts[{v, u}] : 0;
            
            max_matches += min(count_uv, count_vu);
        }
    }
    
    cout << max_matches << "\n";
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (true) {
        if (solve() == -1) break;
    }
    
    return 0;
}
