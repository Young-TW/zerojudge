#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    if (cin >> N) {
        for (int i = 1; i <= N; ++i) {
            int M;
            cin >> M;
            int total_sec = 0;
            int best_sec = 61 * 60; 
            
            for (int j = 0; j < M; ++j) {
                int A, B;
                cin >> A >> B;
                int sec = A * 60 + B;
                total_sec += sec;
                best_sec = min(best_sec, sec);
            }
            
            int avg_sec = total_sec / M;
            
            cout << "Track " << i << ":\n";
            cout << "Best Lap: " << best_sec / 60 << " minute(s) " << best_sec % 60 << " second(s).\n";
            cout << "Average: " << avg_sec / 60 << " minute(s) " << avg_sec % 60 << " second(s).\n";
            if (i < N) {
                cout << "\n";
            }
        }
    }
    
    return 0;
}
