#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        long long total_sum = 0;
        long long current_term = 1;
        long long num = 0;
        bool has_num = false;
        
        for (size_t i = 0; i <= s.length(); ++i) {
            if (i < s.length() && s[i] >= '0' && s[i] <= '9') {
                num = (num * 10 + (s[i] - '0')) % 10000;
                has_num = true;
            } else {
                if (has_num) {
                    current_term = (current_term * num) % 10000;
                    num = 0;
                    has_num = false;
                }
                if (i < s.length()) {
                    if (s[i] == '+') {
                        total_sum = (total_sum + current_term) % 10000;
                        current_term = 1;
                    }
                }
            }
        }
        total_sum = (total_sum + current_term) % 10000;
        cout << total_sum << "\n";
    }
    
    return 0;
}
