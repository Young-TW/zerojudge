#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N, K, A, B, C;
    while (cin >> N >> K >> A >> B >> C) {
        long long t = K + A + B + C;
        if (t > N) cout << -1 << "\n";
        else cout << t << "\n";
    }
    return 0;
}
