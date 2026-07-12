#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    vector<int> last(100005, 0);
    vector<pair<int, int>> intervals;
    
    while (scanf("%d", &T) == 1) {
        while (T--) {
            int N;
            scanf("%d", &N);
            vector<int> arr(N);
            for (int i = 0; i < N; ++i) {
                scanf("%d", &arr[i]);
            }

            intervals.clear();
            for (int i = 0; i < N; ++i) {
                int val = arr[i];
                if (val >= (int)last.size()) {
                    last.resize(val + 1, 0);
                }
                if (last[val] != 0) {
                    intervals.push_back({last[val], i + 1});
                }
                last[val] = i + 1;
            }

            for (int i = 0; i < N; ++i) {
                last[arr[i]] = 0;
            }

            sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
                if (a.second != b.second) return a.second < b.second;
                return a.first < b.first;
            });

            int ans = 0;
            int last_r = 0;
            for (const auto& p : intervals) {
                if (p.first >= last_r) {
                    ans++;
                    last_r = p.second;
                }
            }

            printf("%d\n", ans);
        }
    }
    return 0;
}
