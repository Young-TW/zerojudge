#include <iostream>
#include <string>
#include <cctype>

using namespace std;

long long count2_up_to(long long n) {
    if (n < 0) return 0;
    long long cnt = 0;
    long long factor = 1;
    while (n / factor > 0) {
        long long higher = n / (factor * 10);
        long long curr = (n / factor) % 10;
        long long lower = n % factor;
        
        if (curr < 2) {
            cnt += higher * factor;
        } else if (curr == 2) {
            cnt += higher * factor + lower + 1;
        } else {
            cnt += (higher + 1) * factor;
        }
        factor *= 10;
    }
    return cnt;
}

int main() {
    string s;
    string line;
    while (getline(cin, line)) {
        s += line + "\n";
    }
    
    long long L = -1;
    bool hasL = false;
    size_t i = 0;
    while (i < s.length()) {
        if (i + 12 <= s.length() && s.compare(i, 12, "输入样例") == 0) {
            i += 12;
            while (i < s.length() && !isdigit(s[i])) i++;
            string numStr = "";
            while (i < s.length() && isdigit(s[i])) {
                numStr += s[i];
                i++;
            }
            cout << "输出样例" << numStr << "：" << "\n";
        } else if (isdigit(s[i])) {
            long long val = 0;
            while (i < s.length() && isdigit(s[i])) {
                val = val * 10 + (s[i] - '0');
                i++;
            }
            if (!hasL) {
                L = val;
                hasL = true;
            } else {
                long long R = val;
                long long ans = count2_up_to(R) - count2_up_to(L - 1);
                cout << ans << "\n";
                hasL = false;
            }
        } else {
            i++;
        }
    }
    return 0;
}
