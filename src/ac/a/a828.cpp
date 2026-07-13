#include <iostream>
#include <string>

using namespace std;

int main() {
    long long n;
    while (cin >> n) {
        long long k = (n - 1) / 81;
        long long r = (n - 1) % 81;
        long long L = 3 + k;
        int d1 = (int)(r / 9) + 1;
        int d2idx = (int)(r % 9);
        int d2 = (d2idx < d1) ? d2idx : d2idx + 1;
        string s;
        s.reserve((size_t)L);
        for (long long i = 0; i < L; i++) {
            s += (char)('0' + (((i & 1LL) == 0) ? d1 : d2));
        }
        cout << s << "\n";
    }
    return 0;
}
