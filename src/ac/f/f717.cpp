#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    long long sum = 0;
    int n = 0;
    
    while (cin >> x) {
        sum += x;
        n++;
    }

    if (n == 0) return 0;

    long long ans = sum % n;
    if (ans == 0) {
        ans = n;
    }
    
    cout << ans << "\n";

    return 0;
}
