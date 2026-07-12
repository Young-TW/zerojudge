#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<string, vector<string>> mp;
    
    for (long long i = 32; i <= 99999; ++i) {
        long long sq = i * i;
        string s = to_string(sq);
        bool has_zero = false;
        for (char c : s) {
            if (c == '0') {
                has_zero = true;
                break;
            }
        }
        if (!has_zero) {
            string sorted_s = s;
            sort(sorted_s.begin(), sorted_s.end());
            mp[sorted_s].push_back(s);
        }
    }
    
    string input;
    while (cin >> input) {
        sort(input.begin(), input.end());
        auto it = mp.find(input);
        if (it != mp.end()) {
            bool first = true;
            for (const string& ans : it->second) {
                if (!first) cout << " ";
                cout << ans;
                first = false;
            }
            cout << "\n";
        } else {
            cout << "0\n";
        }
    }
    
    return 0;
}
