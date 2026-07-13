#include <iostream>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        map<int, long long> need, supply;
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            need[x]++;
        }
        for (int i = 0; i < M; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int x;
                cin >> x;
                supply[x]++;
            }
        }
        
        long long extra = 0, missing = 0;
        for (auto& p : need) {
            auto it = supply.find(p.first);
            long long s = (it != supply.end()) ? it->second : 0;
            if (s > p.second) extra += s - p.second;
            else if (p.second > s) missing += p.second - s;
        }
        for (auto& p : supply) {
            if (need.find(p.first) == need.end()) {
                extra += p.second;
            }
        }
        
        cout << extra << " " << missing << "\n";
    }
    return 0;
}
