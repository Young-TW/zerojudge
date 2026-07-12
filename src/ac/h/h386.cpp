#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

using namespace std;

const long double PI = acosl(-1.0L);

void fft(vector<complex<long double>>& a, bool invert) {
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
        long double ang = 2 * PI / len * (invert ? -1 : 1);
        complex<long double> wlen(cosl(ang), sinl(ang));
        for (int i = 0; i < n; i += len) {
            complex<long double> w(1);
            for (int j = 0; j < len / 2; j++) {
                complex<long double> u = a[i + j];
                complex<long double> v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (complex<long double>& x : a) {
            x /= n;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k, n, m;
    while (cin >> k >> n >> m) {
        int len = 1;
        while (len < 2 * k + 1) {
            len <<= 1;
        }
        vector<complex<long double>> a(len), b(len);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a[x] += 1;
        }
        for (int i = 0; i < m; i++) {
            int x;
            cin >> x;
            b[x] += 1;
        }

        fft(a, false);
        fft(b, false);
        for (int i = 0; i < len; i++) {
            a[i] *= b[i];
        }
        fft(a, true);

        for (int i = 2; i <= 2 * k; i++) {
            if (i > 2) cout << " ";
            cout << (long long)roundl(a[i].real());
        }
        cout << "\n";
    }
    return 0;
}
