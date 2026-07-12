#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    while (cin >> N) {
        long long k = N + 1;
        long long ans = 3 * k * k / 2 - 9;
        cout << ans << "\n";
    }
    
    return 0;
}
