#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int K;
    while (cin >> K) {
        int max_score = -2;
        int first_max_time = -1;
        int error_count = 0;
        
        for (int i = 0; i < K; ++i) {
            int t, s;
            cin >> t >> s;
            if (s == -1) {
                error_count++;
            } else {
                if (s > max_score) {
                    max_score = s;
                    first_max_time = t;
                }
            }
        }
        
        int total_score = max_score - K - error_count * 2;
        if (total_score < 0) {
            total_score = 0;
        }
        
        cout << total_score << " " << first_max_time << "\n";
    }
    
    return 0;
}
