#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        vector<pair<int,int>> segs(M);
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &segs[i].first, &segs[i].second);
        }
        sort(segs.begin(), segs.end());
        
        vector<pair<int,int>> merged;
        for (int i = 0; i < M; i++) {
            if (merged.empty() || segs[i].first > merged.back().second) {
                merged.push_back(segs[i]);
            } else {
                if (segs[i].second > merged.back().second)
                    merged.back().second = segs[i].second;
            }
        }
        
        int cur = 0;
        for (size_t i = 0; i < merged.size(); i++) {
            int l = merged[i].first, r = merged[i].second;
            if (cur < l) {
                printf("%d %d\n", cur, l);
            }
            if (r > cur) cur = r;
        }
        if (cur < N) {
            printf("%d %d\n", cur, N);
        }
    }
    return 0;
}
