#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int A, B;
    while (cin >> A >> B) {
        if (A == 0 && B == 0) break;
        
        vector<int> a(A), b(B);
        for (int i = 0; i < A; i++) cin >> a[i];
        for (int i = 0; i < B; i++) cin >> b[i];
        
        set<int> aAll, aDup;
        for (int x : a) {
            if (aAll.count(x)) aDup.insert(x);
            else aAll.insert(x);
        }
        set<int> bAll, bDup;
        for (int x : b) {
            if (bAll.count(x)) bDup.insert(x);
            else bAll.insert(x);
        }
        
        vector<int> aExchange;
        for (int x : aDup) {
            if (!bAll.count(x)) aExchange.push_back(x);
        }
        vector<int> bExchange;
        for (int x : bDup) {
            if (!aAll.count(x)) bExchange.push_back(x);
        }
        
        int mx = (int)min(aExchange.size(), bExchange.size());
        cout << mx << "\n";
        if (mx > 0) {
            cout << "A:";
            for (int x : aExchange) cout << " " << x;
            cout << "\n";
            cout << "B:";
            for (int x : bExchange) cout << " " << x;
            cout << "\n";
        }
    }
    return 0;
}
