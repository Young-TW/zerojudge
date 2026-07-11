#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K) {
        vector<pair<int, int>> acts(N);
        for (int i = 0; i < N; ++i) {
            cin >> acts[i].first;
        }
        for (int i = 0; i < N; ++i) {
            cin >> acts[i].second;
        }
        
        sort(acts.begin(), acts.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.second != b.second) {
                return a.second < b.second;
            }
            return a.first < b.first;
        });
        
        multiset<int> ms;
        int ans = 0;
        
        for (int i = 0; i < N; ++i) {
            int L = acts[i].first;
            int R = acts[i].second;
            
            auto it = ms.lower_bound(L);
            if (it != ms.begin()) {
                --it;
                ms.erase(it);
                ms.insert(R);
                ans++;
            } else {
                if ((int)ms.size() < K) {
                    ms.insert(R);
                    ans++;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
