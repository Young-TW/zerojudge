#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        string s;
        cin >> s;
        
        vector<int> pos;
        for (int i = 0; i < (int)s.length(); i++) {
            if (s[i] == 'A') pos.push_back(i);
        }
        
        int n = pos.size();
        if (n == 0) {
            cout << "P\n";
            continue;
        }
        
        int xorSum = 0;
        int parity = (n - 1) % 2;
        
        // gap before first coin
        if (parity == 0) xorSum ^= pos[0];
        
        // gaps between consecutive coins
        for (int i = 1; i < n; i++) {
            int gap = pos[i] - pos[i-1] - 1;
            if (i % 2 == parity) xorSum ^= gap;
        }
        
        cout << (xorSum ? "N" : "P") << "\n";
    }
    
    return 0;
}
