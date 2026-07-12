#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, L;
    while (cin >> n >> L) {
        vector<pair<int,int>> cuts(n);
        for (int j = 0; j < n; j++) {
            int x, i;
            cin >> x >> i;
            cuts[j] = make_pair(i, x);
        }
        sort(cuts.begin(), cuts.end());
        
        set<int> s;
        s.insert(0);
        s.insert(L);
        
        long long total = 0;
        for (int j = 0; j < n; j++) {
            int x = cuts[j].second;
            set<int>::iterator it = s.upper_bound(x);
            int r = *it;
            int l = *prev(it);
            total += (long long)(r - l);
            s.insert(x);
        }
        
        cout << total << "\n";
    }
    return 0;
}
