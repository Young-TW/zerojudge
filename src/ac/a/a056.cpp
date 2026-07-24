#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

ull gcd(ull a, ull b) {
    while (b) {
        ull t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<bool>> nail(n);
        for (int i = 0; i < n; ++i) {
            nail[i].resize(i + 1);
            for (int j = 0; j <= i; ++j) {
                char c;
                cin >> c;
                nail[i][j] = (c == '*');
            }
        }
        int max_x = 2 * n;
        vector<ull> A(max_x + 1, 0);
        A[n] = 1;
        for (int i = 0; i < n; ++i) {
            vector<bool> exist(max_x + 1, false);
            for (int j = 0; j <= i; ++j) {
                if (nail[i][j]) {
                    int x = n - i + 2 * j;
                    exist[x] = true;
                }
            }
            vector<ull> B(max_x + 1, 0);
            for (int x = 0; x <= max_x; ++x) {
                if (A[x] == 0) continue;
                if (exist[x]) {
                    B[x - 1] += A[x];
                    B[x + 1] += A[x];
                } else {
                    B[x] += A[x] * 2;
                }
            }
            A = move(B);
        }
        ull num = A[2 * m];
        ull den = 1ULL << n;
        if (num == 0) {
            cout << "0/1\n";
        } else {
            ull g = gcd(num, den);
            num /= g;
            den /= g;
            cout << num << '/' << den << '\n';
        }
    }
    return 0;
}
