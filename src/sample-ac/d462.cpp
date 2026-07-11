#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

static const int BASE = 1000000000;
static const int BASE_DIGITS = 9;

int main() {
    int a, n, i, k;
    while (cin >> a >> n >> i >> k) {
        vector<int> num;
        num.reserve(1 << 12);
        num.push_back(1);
        for (int step = 0; step < n; step++) {
            long long carry = 0;
            for (size_t j = 0; j < num.size(); j++) {
                long long v = (long long)num[j] * a + carry;
                num[j] = (int)(v % BASE);
                carry = v / BASE;
            }
            while (carry) {
                num.push_back((int)(carry % BASE));
                carry /= BASE;
            }
        }
        string s;
        s.reserve(num.size() * BASE_DIGITS + 1);
        char buf[16];
        snprintf(buf, sizeof(buf), "%d", num.back());
        s += buf;
        for (int j = (int)num.size() - 2; j >= 0; j--) {
            snprintf(buf, sizeof(buf), "%09d", num[j]);
            s += buf;
        }
        int total = (int)s.size();
        string result;
        result.reserve(k);
        for (int j = 0; j < k; j++) {
            int pos = i - 1 + j;
            if (pos < 0 || pos >= total) break;
            result.push_back(s[pos]);
        }
        cout << result << "\n";
    }
    return 0;
}
