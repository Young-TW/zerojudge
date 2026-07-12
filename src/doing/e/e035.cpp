#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);
const int BASE = 10000;
const int BASE_DIGITS = 4;
typedef complex<double> cd;

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd& x : a) {
            x /= n;
        }
    }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    if (a.empty() || b.empty()) {
        return {};
    }
    if (a.size() < 64 || b.size() < 64) {
        vector<int> res(a.size() + b.size(), 0);
        for (int i = 0; i < a.size(); i++) {
            long long carry = 0;
            for (int j = 0; j < b.size(); j++) {
                long long cur = (long long)a[i] * b[j] + res[i + j] + carry;
                res[i + j] = cur % BASE;
                carry = cur / BASE;
            }
            int k = i + b.size();
            while (carry) {
                long long cur = res[k] + carry;
                res[k] = cur % BASE;
                carry = cur / BASE;
                k++;
            }
        }
        while (res.size() > 1 && res.back() == 0) {
            res.pop_back();
        }
        return res;
    }

    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);

    vector<int> res(n);
    long long carry = 0;
    for (int i = 0; i < n; i++) {
        long long cur = (long long)(round(fa[i].real())) + carry;
        res[i] = cur % BASE;
        carry = cur / BASE;
    }
    while (carry) {
        res.push_back(carry % BASE);
        carry /= BASE;
    }
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}

vector<int> str_to_vec(const string& s) {
    vector<int> res;
    for (int i = s.length(); i > 0; i -= 4) {
        int start = max(0, i - 4);
        int len = i - start;
        res.push_back(stoi(s.substr(start, len)));
    }
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}

string vec_to_str(const vector<int>& v) {
    if (v.empty()) {
        return "0";
    }
    string res = to_string(v.back());
    for (int i = v.size() - 2; i >= 0; i--) {
        string part = to_string(v[i]);
        while (part.length() < 4) {
            part = "0" + part;
        }
        res += part;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string n_str;
    long long m;
    
    while (cin >> n_str >> m) {
        if (n_str == "0" && m == 0) {
            break;
        }
        if (n_str == "1") {
            cout << "1\n";
            continue;
        }
        
        vector<int> base = str_to_vec(n_str);
        vector<int> ans = {1};
        
        while (m > 0) {
            if (m & 1) {
                ans = multiply(ans, base);
            }
            base = multiply(base, base);
            m >>= 1;
        }
        
        cout << vec_to_str(ans) << "\n";
    }
    
    return 0;
}
