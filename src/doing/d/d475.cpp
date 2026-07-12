#include <iostream>
#include <string>

using namespace std;

long long power(long long a, long long n) {
    if (n < 0) {
        if (a == 1) return 1;
        if (a == -1) return (n % 2 == 0) ? 1 : -1;
        return 0;
    }
    long long res = 1;
    while (n > 0) {
        if (n & 1) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, n;
    while (cin >> a >> n) {
        if (a == 0 && n == 0) {
            string line;
            getline(cin, line);
            int extra = 0;
            while (getline(cin, line)) {
                extra++;
            }
            cout << "All Over. Exceeded " << extra << " lines!\n";
            break;
        }
        cout << power(a, n) << "\n";
    }
    return 0;
}
