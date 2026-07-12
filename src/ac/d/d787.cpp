#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        while (n--) {
            string s1, s2;
            cin >> s1 >> s2;
            
            int len1 = s1.length();
            int len2 = s2.length();
            int max_len = max(len1, len2);
            
            int carry = 0;
            int count = 0;
            
            for (int i = 0; i < max_len; ++i) {
                int a = (i < len1) ? (s1[len1 - 1 - i] - '0') : 0;
                int b = (i < len2) ? (s2[len2 - 1 - i] - '0') : 0;
                
                int sum = a + b + carry;
                if (sum >= 10) {
                    carry = 1;
                    count++;
                } else {
                    carry = 0;
                }
            }
            
            cout << count << "\n";
        }
    }
    
    return 0;
}
