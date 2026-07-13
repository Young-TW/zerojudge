#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) continue;
        
        stringstream ss(line);
        int p;
        if (!(ss >> p)) continue;
        if (p == 0) break;
        
        int e;
        ss >> e;
        int X = 1;
        for (int i = 0; i < e; ++i) {
            X *= p;
        }
        
        while (ss >> p >> e) {
            for (int i = 0; i < e; ++i) {
                X *= p;
            }
        }
        
        int n = X - 1;
        vector<pair<int, int>> factors;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                int cnt = 0;
                while (n % i == 0) {
                    n /= i;
                    cnt++;
                }
                factors.push_back({i, cnt});
            }
        }
        if (n > 1) {
            factors.push_back({n, 1});
        }
        
        for (int i = factors.size() - 1; i >= 0; --i) {
            cout << factors[i].first << " " << factors[i].second;
            if (i > 0) cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
