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
        long long current_product = 1;
        long long current_num = 0;
        bool has_num = false;
        
        for (char c : s) {
            if (c >= '0' && c <= '9') {
                current_num = current_num * 10 + (c - '0');
                has_num = true;
            } else if (c == '*') {
                current_product = (current_product * current_num) % 100000;
                current_num = 0;
            } else if (c == '+') {
                current_product = (current_product * current_num) % 100000;
                total_sum = (total_sum + current_product) % 100000;
                current_product = 1;
                current_num = 0;
            }
        }
        
        if (has_num) {
            current_product = (current_product * current_num) % 100000;
            total_sum = (total_sum + current_product) % 100000;
        }
        
        cout << total_sum << "\n";
    }
    
    return 0;
}
