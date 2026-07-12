#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    cin.ignore();
    
    while (T--) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        
        vector<int> weights;
        int w;
        int total = 0;
        while (iss >> w) {
            weights.push_back(w);
            total += w;
        }
        
        if (total % 2 != 0) {
            cout << "NO\n";
        } else {
            int target = total / 2;
            bitset<4005> dp;
            dp[0] = 1;
            for (int weight : weights) {
                dp |= (dp << weight);
            }
            if (dp[target]) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    
    return 0;
}
