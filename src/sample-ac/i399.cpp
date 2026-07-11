#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c;
    while (cin >> a >> b >> c) {
        int cnt[10] = {0};
        cnt[a]++;
        cnt[b]++;
        cnt[c]++;
        
        int P = 0;
        for (int i = 1; i <= 9; ++i) {
            P = max(P, cnt[i]);
        }
        
        vector<int> v = {a, b, c};
        sort(v.begin(), v.end(), greater<int>());
        v.erase(unique(v.begin(), v.end()), v.end());
        
        cout << P;
        for (int x : v) {
            cout << " " << x;
        }
        cout << "\n";
    }
    
    return 0;
}
