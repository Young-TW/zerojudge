#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_COORD = 100005;
int diff[MAX_COORD];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Y;
    while (cin >> N >> Y) {
        memset(diff, 0, sizeof(diff));
        for (int i = 0; i < N; ++i) {
            int A, B;
            cin >> A >> B;
            int L = max(1, B - Y);
            int R = A;
            if (L <= R) {
                diff[L]++;
                diff[R + 1]--;
            }
        }
        
        int max_cnt = 0;
        int current_cnt = 0;
        int best_C_count = 0;
        
        for (int i = 1; i <= 100000; ++i) {
            current_cnt += diff[i];
            if (current_cnt > max_cnt) {
                max_cnt = current_cnt;
                best_C_count = 1;
            } else if (current_cnt == max_cnt) {
                best_C_count++;
            }
        }
        
        cout << best_C_count << " " << max_cnt << "\n";
    }
    
    return 0;
}
