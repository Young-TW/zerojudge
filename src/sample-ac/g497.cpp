#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        long long ans = 0;
        int curr = 1;
        for (int i = 0; i < n; ++i) {
            int next;
            cin >> next;
            if (next > curr) {
                ans += (long long)(next - curr) * 3;
            } else if (next < curr) {
                ans += (long long)(curr - next) * 2;
            }
            curr = next;
        }
        cout << ans << '\n';
    }
    
    return 0;
}
