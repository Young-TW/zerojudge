#include <iostream>
#include <vector>
#include <string>
using namespace std;

static const unsigned int BASE = 1000000000U;

typedef vector<unsigned int> Big; // little-endian, base 1e9

static void mulSmall(Big &a, unsigned long long m) {
    unsigned long long carry = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        unsigned long long cur = (unsigned long long)a[i] * m + carry;
        a[i] = (unsigned int)(cur % BASE);
        carry = cur / BASE;
    }
    while (carry > 0) {
        a.push_back((unsigned int)(carry % BASE));
        carry /= BASE;
    }
}

static void divSmall(Big &a, unsigned long long d) { // exact division
    unsigned long long rem = 0;
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        unsigned long long cur = (unsigned long long)a[i] + rem * (unsigned long long)BASE;
        a[i] = (unsigned int)(cur / d);
        rem = cur % d;
    }
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

static string toStr(const Big &a) {
    string s = to_string((unsigned long long)a.back());
    for (int i = (int)a.size() - 2; i >= 0; --i) {
        string t = to_string((unsigned long long)a[i]);
        s.append(9 - t.size(), '0');
        s += t;
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> qs;
    int n, maxn = 0;
    while (cin >> n) {
        if (n == 0) break;
        qs.push_back(n);
        if (n > maxn) maxn = n;
    }

    // Catalan numbers: C(0)=1, C(i) = C(i-1) * (4i-2) / (i+1)
    vector<string> cat(maxn + 1);
    Big c(1, 1);
    if (maxn >= 0) cat[0] = "1";
    for (int i = 1; i <= maxn; ++i) {
        mulSmall(c, (unsigned long long)(4 * i - 2));
        divSmall(c, (unsigned long long)(i + 1));
        cat[i] = toStr(c);
    }

    for (size_t i = 0; i < qs.size(); ++i) {
        cout << cat[qs[i]] << "\n";
    }
    return 0;
}
