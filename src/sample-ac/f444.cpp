#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <numeric>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        long long x;
        stringstream ss1(line);
        if (!(ss1 >> x)) {
            continue;
        }
        
        if (!getline(cin, line)) break;
        stringstream ss2(line);
        vector<long long> coeffs;
        long long c;
        while (ss2 >> c) {
            coeffs.push_back(c);
        }
        
        if (coeffs.empty()) {
            cout << 0 << "\n";
            continue;
        }
        
        long long ans = 0;
        int n = coeffs.size();
        for (int i = 0; i < n - 1; ++i) {
            ans = ans * x + coeffs[i] * (n - 1 - i);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
