#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            cout << "\n";
            continue;
        }
        size_t sp1 = line.find(' ');
        size_t sp2 = line.rfind(' ');
        string a = line.substr(0, sp1);
        char op = line[sp1 + 1];
        string b = line.substr(sp2 + 1);
        
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        
        int count = 0;
        if (op == '+') {
            int carry = 0;
            size_t n = max(a.size(), b.size());
            for (size_t i = 0; i < n; i++) {
                int da = i < a.size() ? a[i] - '0' : 0;
                int db = i < b.size() ? b[i] - '0' : 0;
                int sum = da + db + carry;
                if (sum >= 10) {
                    carry = 1;
                    count++;
                } else {
                    carry = 0;
                }
            }
        } else {
            int borrow = 0;
            size_t n = a.size();
            for (size_t i = 0; i < n; i++) {
                int da = a[i] - '0';
                int db = i < b.size() ? b[i] - '0' : 0;
                int diff = da - db - borrow;
                if (diff < 0) {
                    borrow = 1;
                    count++;
                } else {
                    borrow = 0;
                }
            }
        }
        cout << count << "\n";
    }
    return 0;
}
