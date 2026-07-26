#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);

void fft(vector<complex<double>>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        complex<double> wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            complex<double> w(1);
            for (int j = 0; j < len/2; ++j) {
                complex<double> u = a[i+j];
                complex<double> v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; ++i)
            a[i] /= n;
    }
}

void fft2d(vector<vector<complex<double>>>& a, bool invert) {
    int n = a.size();
    int m = a[0].size();
    for (int i = 0; i < n; ++i)
        fft(a[i], invert);
    for (int j = 0; j < m; ++j) {
        vector<complex<double>> col(n);
        for (int i = 0; i < n; ++i)
            col[i] = a[i][j];
        fft(col, invert);
        for (int i = 0; i < n; ++i)
            a[i][j] = col[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int A_H, A_W, B_H, B_W;
    while (cin >> A_H >> A_W >> B_H >> B_W) {
        vector<vector<int>> A(A_H, vector<int>(A_W));
        for (int i = 0; i < A_H; ++i)
            for (int j = 0; j < A_W; ++j)
                cin >> A[i][j];

        vector<vector<int>> B(B_H, vector<int>(B_W));
        for (int i = 0; i < B_H; ++i)
            for (int j = 0; j < B_W; ++j)
                cin >> B[i][j];

        long long constB = 0;
        for (int i = 0; i < B_H; ++i)
            for (int j = 0; j < B_W; ++j)
                constB += (long long)B[i][j] * B[i][j];

        vector<vector<long long>> pref(A_H + 1, vector<long long>(A_W + 1, 0));
        for (int i = 0; i < A_H; ++i) {
            for (int j = 0; j < A_W; ++j) {
                long long val = (long long)A[i][j] * A[i][j];
                pref[i+1][j+1] = pref[i][j+1] + pref[i+1][j] - pref[i][j] + val;
            }
        }

        vector<vector<int>> B_rot(B_H, vector<int>(B_W));
        for (int i = 0; i < B_H; ++i)
            for (int j = 0; j < B_W; ++j)
                B_rot[i][j] = B[B_H - 1 - i][B_W - 1 - j];

        int N = 1, M = 1;
        while (N < A_H + B_H - 1) N <<= 1;
        while (M < A_W + B_W - 1) M <<= 1;

        vector<vector<complex<double>>> FA(N, vector<complex<double>>(M, 0));
        vector<vector<complex<double>>> FB(N, vector<complex<double>>(M, 0));

        for (int i = 0; i < A_H; ++i)
            for (int j = 0; j < A_W; ++j)
                FA[i][j] = complex<double>(A[i][j], 0);

        for (int i = 0; i < B_H; ++i)
            for (int j = 0; j < B_W; ++j)
                FB[i][j] = complex<double>(B_rot[i][j], 0);

        fft2d(FA, false);
        fft2d(FB, false);

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                FA[i][j] *= FB[i][j];

        fft2d(FA, true);

        long long min_diff = LLONG_MAX;
        int best_x = 1, best_y = 1;

        for (int i = 0; i <= A_H - B_H; ++i) {
            for (int j = 0; j <= A_W - B_W; ++j) {
                long long sumA2 = pref[i + B_H][j + B_W] - pref[i][j + B_W] - pref[i + B_H][j] + pref[i][j];
                complex<double> cval = FA[i + B_H - 1][j + B_W - 1];
                long long cross = (long long)(cval.real() + 0.5);
                long long diff = sumA2 + constB - 2 * cross;
                if (diff < min_diff) {
                    min_diff = diff;
                    best_x = i + 1;
                    best_y = j + 1;
                }
            }
        }

        cout << best_x << " " << best_y << "\n";
    }

    return 0;
}
