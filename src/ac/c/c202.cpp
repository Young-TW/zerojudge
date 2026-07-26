#include <iostream>
#include <string>
#include <cctype>
using namespace std;

long long gcd_ll(long long a, long long b) {
    while (b) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

bool isAllDigits(const string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string token;
    while (cin >> token) {
        if (isAllDigits(token)) {
            int n = stoi(token);
            long long g = 0;
            for (int i = 0; i < n; ++i) {
                long long x;
                cin >> x;
                if (i == 0) g = x;
                else g = gcd_ll(g, x);
            }
            cout << g << '\n';
        } else {
            string output = token;
            for (size_t i = 0; i + 2 < output.size(); ++i) {
                if ((unsigned char)output[i] == 0xE5 && 
                    (unsigned char)output[i+1] == 0x85 && 
                    (unsigned char)output[i+2] == 0xA5) {
                    output[i+1] = (char)0x87;
                    output[i+2] = (char)0xBA;
                    break;
                }
            }
            cout << output << '\n';
        }
    }
    return 0;
}
