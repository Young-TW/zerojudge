#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    
    bool hasOutput = false;
    
    for (size_t i = 0; i < lines.size(); ) {
        const string& l = lines[i];
        size_t start = l.find_first_not_of(" \t\r");
        if (start == string::npos) {
            i++;
            continue;
        }
        if (start + 1 < l.size() && l[start] == '/' && l[start + 1] == '/') {
            if (hasOutput) cout << "\n";
            cout << l << "\n";
            hasOutput = true;
            i++;
            continue;
        }
        stringstream ss(l);
        long long n;
        if (!(ss >> n)) {
            i++;
            continue;
        }
        vector<long long> a;
        long long val;
        while (a.size() < (size_t)n && ss >> val) {
            a.push_back(val);
        }
        while (a.size() < (size_t)n) {
            i++;
            if (i >= lines.size()) break;
            stringstream ss2(lines[i]);
            while (a.size() < (size_t)n && ss2 >> val) {
                a.push_back(val);
            }
        }
        i++;
        
        if ((size_t)n != a.size()) continue;
        
        vector<vector<long long>> dp(n, vector<long long>(n, 0));
        for (int len = 2; len < n; len++) {
            for (int ii = 0; ii + len < n; ii++) {
                int jj = ii + len;
                dp[ii][jj] = LLONG_MAX;
                for (int k = ii + 1; k < jj; k++) {
                    long long v = dp[ii][k] + dp[k][jj] + a[ii] * a[k] * a[jj];
                    if (v < dp[ii][jj]) dp[ii][jj] = v;
                }
            }
        }
        cout << dp[0][n - 1] << "\n";
        hasOutput = true;
    }
    return 0;
}
