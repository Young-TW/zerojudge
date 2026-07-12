#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> queries;
    int n;
    while (cin >> n && n != 0) {
        queries.push_back(n);
    }
    
    if (queries.empty()) return 0;
    
    vector<pair<int, int>> sorted_queries;
    for (size_t i = 0; i < queries.size(); ++i) {
        sorted_queries.push_back({queries[i], i});
    }
    sort(sorted_queries.begin(), sorted_queries.end());
    
    vector<string> ans(queries.size());
    
    vector<int> num;
    num.reserve(3100);
    num.push_back(1);
    
    size_t q_idx = 0;
    int current_power = 0;
    
    while (q_idx < sorted_queries.size()) {
        int target_power = sorted_queries[q_idx].first;
        
        while (current_power < target_power) {
            int carry = 0;
            for (size_t j = 0; j < num.size(); ++j) {
                int val = num[j] * 2 + carry;
                num[j] = val % 10;
                carry = val / 10;
            }
            if (carry) {
                num.push_back(carry);
            }
            current_power++;
        }
        
        string s;
        s.reserve(num.size());
        for (int j = num.size() - 1; j >= 0; --j) {
            s += (char)('0' + num[j]);
        }
        ans[sorted_queries[q_idx].second] = s;
        q_idx++;
    }
    
    for (size_t i = 0; i < ans.size(); ++i) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}
