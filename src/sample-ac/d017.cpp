#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    int case_num = 1;
    bool first_case = true;
    
    while (cin >> s) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        int n = s.length();
        int a_count = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'a') {
                a_count++;
            }
        }
        int b_count = n - a_count;
        
        vector<pair<int, int>> ans;
        for (int i = 0; i < n; ++i) {
            int j1 = (i + a_count) % n;
            if (i < j1) {
                ans.push_back(make_pair(i, j1));
            }
            int j2 = (i + b_count) % n;
            if (i < j2) {
                ans.push_back(make_pair(i, j2));
            }
        }
        
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        
        cout << "AB Circle #" << case_num++ << ":\n";
        for (size_t i = 0; i < ans.size(); ++i) {
            cout << ans[i].first << "," << ans[i].second << "\n";
        }
    }
    
    return 0;
}
