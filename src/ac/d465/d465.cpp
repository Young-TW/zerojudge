#include <bits/stdc++.h>
using namespace std;

// d465: output a^n's k digits starting from position i (1-indexed, most-significant first).
// Big integer via base-1e9 limbs, computed by repeated multiplication by small a.
// NOTE: the problem-statement sample is indented (markdown code fence), so the local
// 1.out carries spurious leading spaces. The real judge format has NO leading spaces.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long long BASE = 1000000000LL; // 1e9
    long long a, n, i, k;
    while (cin >> a >> n >> i >> k){
        vector<long long> num;
        num.reserve(6000);
        num.push_back(1);
        for (long long step = 0; step < n; ++step){
            long long carry = 0;
            for (size_t j = 0; j < num.size(); ++j){
                long long cur = num[j] * a + carry;
                num[j] = cur % BASE;
                carry = cur / BASE;
            }
            while (carry){
                num.push_back(carry % BASE);
                carry /= BASE;
            }
        }
        string s;
        s.reserve(num.size() * 9);
        s = to_string(num.back());
        char buf[16];
        for (int j = (int)num.size() - 2; j >= 0; --j){
            snprintf(buf, sizeof(buf), "%09lld", num[j]);
            s += buf;
        }
        long long len = (long long)s.size();
        string out;
        if (i <= len){
            long long start = i - 1;
            long long take = min(k, len - start);
            out = s.substr(start, take);
        }
        cout << out << '\n';
    }
    return 0;
}
