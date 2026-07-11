#include <iostream>
#include <cstdint>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            uint32_t A, B;
            cin >> A >> B;
            ans += __builtin_popcount(~A & B);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
