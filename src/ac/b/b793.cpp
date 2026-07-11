#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> max_time(N, 0); // max finish time for each initial position p
        
        for (int i = 0; i < N; ++i) {
            vector<int> q(N);
            for (int j = 0; j < N; ++j) {
                cin >> q[j];
                --q[j]; // 0-indexed dishes
            }
            
            // Compute a[k] = (q[k] - i) mod N
            vector<int> a(N);
            for (int k = 0; k < N; ++k) {
                a[k] = (q[k] - i + N) % N;
            }
            
            // Difference array for C(p) = number of k where r_k <= r_{k-1}
            vector<int> diff(N + 1, 0);
            for (int k = 1; k < N; ++k) {
                int x = a[k-1];
                int y = a[k];
                if (y > x) {
                    int L = N - y;
                    int R = N - x - 1;
                    diff[L]++;
                    diff[R+1]--;
                } else { // y < x (since a is a permutation)
                    diff[0]++;
                    diff[N]--;
                    int L = N - x;
                    int R = N - y - 1;
                    diff[L]--;
                    diff[R+1]++;
                }
            }
            
            // Compute C(p) and finish time f(p) for this guest
            vector<int> C(N);
            int cur = 0;
            for (int p = 0; p < N; ++p) {
                cur += diff[p];
                C[p] = cur;
            }
            
            for (int p = 0; p < N; ++p) {
                int R = (a[N-1] + p) % N;
                int finish = C[p] * N + R;
                if (finish > max_time[p]) max_time[p] = finish;
            }
        }
        
        int ans = *min_element(max_time.begin(), max_time.end());
        cout << ans << '\n';
    }
    return 0;
}
