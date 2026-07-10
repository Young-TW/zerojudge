#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// KMP: does pattern occur in text?
static bool kmp(const string& text, const string& pat) {
    int m = (int)pat.size();
    if (m == 0) return true;
    // failure function
    vector<int> f(m, 0);
    for (int i = 1; i < m; i++) {
        int k = f[i - 1];
        while (k > 0 && pat[k] != pat[i]) k = f[k - 1];
        if (pat[k] == pat[i]) k++;
        f[i] = k;
    }
    int n = (int)text.size();
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && pat[j] != text[i]) j = f[j - 1];
        if (pat[j] == text[i]) j++;
        if (j == m) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    while (cin >> a >> b) {
        if (a.size() != b.size()) {
            cout << "difference\n";
            continue;
        }
        if (a.empty()) {
            cout << "same\n";
            continue;
        }
        string aa = a + a;
        bool ok = kmp(aa, b);
        if (!ok) {
            string rb = b;
            reverse(rb.begin(), rb.end());
            ok = kmp(aa, rb);
        }
        cout << (ok ? "same\n" : "difference\n");
    }
    return 0;
}
