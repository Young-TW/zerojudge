#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        string a_str = s;
        sort(a_str.rbegin(), a_str.rend());
        
        string b_str = s;
        sort(b_str.begin(), b_str.end());
        
        if (b_str[0] == '0') {
            size_t idx = 0;
            while (idx < b_str.length() && b_str[idx] == '0') {
                idx++;
            }
            if (idx < b_str.length()) {
                swap(b_str[0], b_str[idx]);
            }
        }
        
        long long a = stoll(a_str);
        long long b = stoll(b_str);
        long long diff = a - b;
        long long x = diff / 9;
        
        cout << a << " - " << b << " = " << diff << " = 9 * " << x << "\n";
    }
    
    return 0;
}
