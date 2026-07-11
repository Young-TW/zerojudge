#include <iostream>

using namespace std;

long long solve(long long a, long long b) {
    if (a == b) return 1;
    if (a > b) return 2 * solve(a - b, b);
    return 2 * solve(b - a, a) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long a, b;
    while (cin >> a >> b) {
        cout << solve(a, b) << "\n";
    }
    return 0;
}
