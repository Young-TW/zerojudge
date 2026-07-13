#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int charToVal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 36;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    while (cin >> s) {
        long long sum = 0;
        int max_d = 0;
        for (size_t i = 0; i < s.length(); ++i) {
            int val = charToVal(s[i]);
            if (val == -1) continue;
            sum += val;
            if (val > max_d) {
                max_d = val;
            }
        }
        
        bool found = false;
        int start_N = max(max_d + 1, 2);
        for (int N = start_N; N <= 62; ++N) {
            if (sum % (N - 1) == 0) {
                cout << N << "\n";
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "such number is impossible!\n";
        }
    }
    return 0;
}
