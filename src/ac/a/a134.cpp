#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        while (N--) {
            long long n;
            cin >> n;
            vector<long long> fib;
            long long a = 1, b = 2;
            fib.push_back(a);
            if (b <= n) fib.push_back(b);
            while (true) {
                long long c = a + b;
                if (c > n) break;
                fib.push_back(c);
                a = b;
                b = c;
            }
            string s;
            long long rem = n;
            for (int j = (int)fib.size() - 1; j >= 0; j--) {
                if (fib[j] <= rem) {
                    s += '1';
                    rem -= fib[j];
                } else {
                    s += '0';
                }
            }
            cout << n << " = " << s << " (fib)\n";
        }
    }
    return 0;
}
