#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    vector<string> inputs;
    while (cin >> s) {
        inputs.push_back(s);
    }
    
    int n = inputs.size();
    vector<long long> ans(n, 0);
    vector<pair<long long, int>> valid;
    
    for (int i = 0; i < n; ++i) {
        const string& str = inputs[i];
        size_t start = 0;
        while (start < str.length() - 1 && str[start] == '0') {
            start++;
        }
        string trimmed_str = str.substr(start);
        
        bool ge_mod = false;
        if (trimmed_str.length() > 10) {
            ge_mod = true;
        } else if (trimmed_str.length() == 10) {
            if (trimmed_str >= "1000000007") {
                ge_mod = true;
            }
        }
        
        if (ge_mod) {
            ans[i] = 0;
        } else {
            long long val = 0;
            for (char c : trimmed_str) {
                val = val * 10 + (c - '0');
            }
            valid.push_back({val, i});
        }
    }
    
    sort(valid.begin(), valid.end());
    
    long long current_fact = 1;
    long long current_n = 0;
    
    for (size_t i = 0; i < valid.size(); ++i) {
        long long target = valid[i].first;
        for (long long j = current_n + 1; j <= target; ++j) {
            current_fact = (current_fact * j) % MOD;
        }
        current_n = target;
        ans[valid[i].second] = current_fact;
    }
    
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}
