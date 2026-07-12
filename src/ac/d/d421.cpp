#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long to_int(const string& s) {
    if (s.empty()) return 0;
    long long res = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        res = res * 10 + (s[i] - '0');
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long pow10[15];
    pow10[0] = 1;
    for (int i = 1; i < 15; ++i) {
        pow10[i] = pow10[i - 1] * 10;
    }
    
    int j;
    int case_num = 1;
    while (cin >> j) {
        if (j == -1) break;
        string s;
        cin >> s;
        
        size_t dot_pos = s.find('.');
        string digits = (dot_pos != string::npos) ? s.substr(dot_pos + 1) : "";
        
        int len = digits.length();
        int k = len - j;
        if (k < 0) k = 0;
        
        long long N, D;
        
        if (j == 0) {
            N = to_int(digits);
            D = pow10[k];
        } else {
            string first_part = digits.substr(0, k);
            N = to_int(digits) - to_int(first_part);
            D = pow10[len] - pow10[k];
        }
        
        if (N == 0) {
            D = 1;
        } else {
            long long g = gcd(N, D);
            N /= g;
            D /= g;
        }
        
        if (D < 0) {
            N = -N;
            D = -D;
        }
        
        cout << "Case " << case_num << ": " << N << "/" << D << "\n";
        case_num++;
    }
    
    return 0;
}
