#include <iostream>
using namespace std;

int main() {
    long long a, b, N;
    while (cin >> a >> b >> N) {
        // integer part
        long long ip = a / b;
        long long r = a % b;
        cout << ip << '.';
        for (int i = 0; i < N; i++) {
            r *= 10;
            cout << (r / b);
            r %= b;
        }
        cout << '\n';
    }
    return 0;
}
