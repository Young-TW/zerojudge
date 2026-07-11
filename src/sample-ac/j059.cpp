#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        long long n;
        cin >> n;
        long long r = 315LL * n + 36962LL;
        long long a = (r < 0) ? -r : r;
        long long tens = (a / 10) % 10;
        cout << tens << "\n";
    }
    return 0;
}
