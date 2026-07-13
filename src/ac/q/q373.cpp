#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    while (cin >> N) {
        long long total_intervals = N * (N + 1) / 2;
        long long equal_intervals = 0;
        long long current_len = 0;
        int prev_val = -1;
        
        for (long long i = 0; i < N; ++i) {
            int x;
            cin >> x;
            if (x == prev_val) {
                current_len++;
            } else {
                current_len = 1;
            }
            equal_intervals += current_len;
            prev_val = x;
        }
        
        long long less_intervals = total_intervals - equal_intervals;
        cout << less_intervals << " " << equal_intervals << " " << 0 << "\n";
    }
    
    return 0;
}
