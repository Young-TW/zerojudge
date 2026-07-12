#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    string dummy;
    getline(cin, dummy); // 讀取 T 後面的換行
    
    for (int t = 0; t < T; ++t) {
        string line;
        // 讀取直到非空白行，以應對可能的多個空白行
        while (getline(cin, line)) {
            bool all_space = true;
            for (size_t i = 0; i < line.size(); ++i) {
                if (!isspace(static_cast<unsigned char>(line[i]))) {
                    all_space = false;
                    break;
                }
            }
            if (!all_space) break;
        }
        
        stringstream ss_p(line);
        vector<int> p;
        int val;
        while (ss_p >> val) {
            p.push_back(val);
        }
        
        getline(cin, line);
        stringstream ss_x(line);
        vector<string> x;
        string s_val;
        while (ss_x >> s_val) {
            x.push_back(s_val);
        }
        
        int n = p.size();
        vector<string> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[p[i] - 1] = x[i];
        }
        
        if (t > 0) cout << "\n";
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << "\n";
        }
    }
    
    return 0;
}
