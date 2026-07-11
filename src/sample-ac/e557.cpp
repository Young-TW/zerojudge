#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int A, B;
    while (cin >> A >> B) {
        if (A == 0 && B == 0) break;
        
        vector<int> a(A), b(B);
        for (int i = 0; i < A; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < B; ++i) {
            cin >> b[i];
        }
        
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        
        a.erase(unique(a.begin(), a.end()), a.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        
        vector<int> common_cards;
        set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(common_cards));
        int common = common_cards.size();
        
        int alice_only = a.size() - common;
        int betty_only = b.size() - common;
        
        cout << min(alice_only, betty_only) << "\n";
    }
    
    return 0;
}
