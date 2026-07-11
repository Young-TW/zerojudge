#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool is_leap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

bool is_palindrome(const string& s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    while (n--) {
        int Y;
        cin >> Y;
        
        int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (is_leap(Y)) {
            days_in_month[2] = 29;
        }
        
        vector<long long> ans;
        string year_str = to_string(Y);
        
        for (int m = 1; m <= 12; ++m) {
            for (int d = 1; d <= days_in_month[m]; ++d) {
                vector<string> m_strs;
                string m_str = to_string(m);
                if (m < 10) {
                    m_strs.push_back(m_str);
                    m_strs.push_back("0" + m_str);
                } else {
                    m_strs.push_back(m_str);
                }
                
                vector<string> d_strs;
                string d_str = to_string(d);
                if (d < 10) {
                    d_strs.push_back(d_str);
                    d_strs.push_back("0" + d_str);
                } else {
                    d_strs.push_back(d_str);
                }
                
                for (const string& ms : m_strs) {
                    for (const string& ds : d_strs) {
                        string s = year_str + ms + ds;
                        if (is_palindrome(s)) {
                            ans.push_back(stoll(s));
                        }
                    }
                }
            }
        }
        
        sort(ans.begin(), ans.end());
        
        cout << ans.size();
        for (long long x : ans) {
            cout << " " << x;
        }
        cout << "\n";
    }
    
    return 0;
}
