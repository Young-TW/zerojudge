#include <iostream>

using namespace std;

const int MAXN = 1000000;
int factor_count[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 2; i <= MAXN; ++i) {
        if (factor_count[i] == 0) {
            for (int j = i; j <= MAXN; j += i) {
                factor_count[j]++;
            }
        }
    }

    int n;
    while (cin >> n && n != 0) {
        cout << n << " : " << factor_count[n] << "\n";
    }

    return 0;
}
