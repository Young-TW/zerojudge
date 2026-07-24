#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, K;
    while (std::cin >> N >> K) {
        std::vector<int> A(N), B(N);
        for (int i = 0; i < N; ++i) std::cin >> A[i];
        for (int i = 0; i < N; ++i) std::cin >> B[i];
        
        // diff[i] = how many +1 operations are needed at position i (mod 9)
        std::vector<int> diff(N);
        for (int i = 0; i < N; ++i) {
            diff[i] = (B[i] - A[i] + 9) % 9;
        }
        
        std::vector<int> expire(N + K + 1, 0);   // expire[pos] = total increments that stop affecting at pos
        int cur = 0;                             // current cumulative increments affecting position i (mod 9)
        long long ans = 0;
        bool ok = true;
        
        for (int i = 0; i < N; ++i) {
            // remove increments that expired at this position
            cur = (cur - expire[i] + 9) % 9;
            
            int need = (diff[i] - cur + 9) % 9;   // how many new operations must start at i
            if (need) {
                if (i + K > N) {                 // cannot start a length‑K segment here
                    ok = false;
                    break;
                }
                ans += need;
                cur = (cur + need) % 9;
                expire[i + K] = (expire[i + K] + need) % 9; // these increments will disappear after position i+K-1
            }
        }
        
        if (!ok) std::cout << 0 << '\n';
        else     std::cout << ans << '\n';
    }
    return 0;
}
