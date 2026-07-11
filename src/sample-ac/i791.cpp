#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K;
    while (cin >> N >> K) {
        int count[101];
        memset(count, 0, sizeof(count));
        for (int i = 0; i < N; ++i) {
            int c;
            cin >> c;
            count[c]++;
        }
        long long ans = 0;
        for (int i = 0; i <= 100; ++i) {
            ans += count[i] / K;
        }
        cout << ans << '\n';
    }
    return 0;
}
