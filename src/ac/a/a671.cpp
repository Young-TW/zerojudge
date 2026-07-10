#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

static string mul(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<int> r(n + m, 0);
    for (int i = n - 1; i >= 0; i--) {
        int di = a[i] - '0';
        for (int j = m - 1; j >= 0; j--) {
            r[i + j + 1] += di * (b[j] - '0');
        }
    }
    for (int i = n + m - 1; i > 0; i--) {
        r[i - 1] += r[i] / 10;
        r[i] %= 10;
    }
    int start = 0;
    while (start < n + m - 1 && r[start] == 0) start++;
    string s;
    s.reserve(n + m - start);
    for (int i = start; i < n + m; i++) s += char('0' + r[i]);
    return s;
}

static string powstr(const string& base, int e) {
    string r = "1";
    for (int i = 0; i < e; i++) r = mul(r, base);
    return r;
}

int main() {
    int n;
    string p;
    while (cin >> n >> p) {
        long double pl = stold(p);
        long double kld = powl(pl, 1.0L / n);
        long long k = llroundl(kld);
        for (long long kk = k - 2; kk <= k + 2; kk++) {
            if (kk < 1) continue;
            string cand = powstr(to_string(kk), n);
            if (cand == p) {
                cout << kk << "\n";
                break;
            }
        }
    }
    return 0;
}
