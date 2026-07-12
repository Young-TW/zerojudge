#include <iostream>
#include <string>
#include <algorithm>

std::string multiply(const std::string& s, int n) {
    if (n == 0 || s == "0") return "0";
    int carry = 0;
    std::string res = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        int prod = (s[i] - '0') * n + carry;
        res += (char)('0' + prod % 10);
        carry = prod / 10;
    }
    while (carry > 0) {
        res += (char)('0' + carry % 10);
        carry /= 10;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    long long N, D;
    while (std::cin >> N >> D) {
        if (N == 0 && D == 0) break;
        std::string ans = "1";
        for (long long i = 0; i < D; i++) {
            ans = multiply(ans, N);
        }
        std::cout << ans << "\n";
    }
    return 0;
}
