#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    
    for (int i = 0; i < n; ++i) {
        string line;
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (!line.empty()) break;
        }
        
        unordered_map<string, long long> species;
        long long total = 0;
        
        if (!line.empty()) {
            species[line]++;
            total++;
            while (getline(cin, line)) {
                if (!line.empty() && line.back() == '\r') {
                    line.pop_back();
                }
                if (line.empty()) break;
                species[line]++;
                total++;
            }
        }
        
        vector<pair<string, long long>> vec(species.begin(), species.end());
        sort(vec.begin(), vec.end());
        
        if (i > 0) cout << "\n";
        
        for (const auto& p : vec) {
            double percentage = (double)p.second * 100.0 / total;
            cout << p.first << " " << fixed << setprecision(4) << percentage << "\n";
        }
    }
    
    return 0;
}
