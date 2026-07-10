#include <iostream>
using namespace std;

int main() {
    long long n;
    while (cin >> n) {
        for (long long i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                cout << (n / i) << "\n";
                break;
            }
        }
    }
    return 0;
}
