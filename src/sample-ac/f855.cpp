#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<pair<int, int>> segs(N);
        for (int i = 0; i < N; ++i) {
            cin >> segs[i].first >> segs[i].second;
            if (segs[i].first > segs[i].second) {
                swap(segs[i].first, segs[i].second);
            }
        }
        
        sort(segs.begin(), segs.end());
        
        long long total_length = 0;
        if (N > 0) {
            int curL = segs[0].first;
            int curR = segs[0].second;
            for (int i = 1; i < N; ++i) {
                if (segs[i].first <= curR) {
                    if (segs[i].second > curR) {
                        curR = segs[i].second;
                    }
                } else {
                    total_length += curR - curL;
                    curL = segs[i].first;
                    curR = segs[i].second;
                }
            }
            total_length += curR - curL;
        }
        
        cout << total_length << "\n";
    }
    
    return 0;
}
