#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> evens, odds;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (x % 2 == 0) {
                evens.push_back(x);
            } else {
                odds.push_back(x);
            }
        }
        
        sort(evens.begin(), evens.end());
        sort(odds.begin(), odds.end(), greater<int>());
        
        bool first = true;
        for (int x : evens) {
            if (!first) cout << " ";
            cout << x;
            first = false;
        }
        for (int x : odds) {
            if (!first) cout << " ";
            cout << x;
            first = false;
        }
        cout << "\n";
    }
    
    return 0;
}
