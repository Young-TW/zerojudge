#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        while (N--) {
            unsigned long long A, B;
            cin >> A >> B;
            unsigned long long X = A ^ B;
            unsigned long long Y = 0;
            if (X > 0) {
                int shift = 64 - __builtin_clzll(X);
                unsigned long long p = 1ULL << shift;
                Y = p - X;
            }
            cout << X << " " << Y << "\n";
        }
    }
    return 0;
}
