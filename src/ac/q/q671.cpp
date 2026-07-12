#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, T, L, R;
    while (cin >> N >> T >> L >> R) {
        vector<int> w(N);
        for (int i = 0; i < N; ++i) {
            cin >> w[i];
        }
        
        int left = L, right = R, ans = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int trips = 1;
            int current_weight = 0;
            
            for (int i = 0; i < N; ++i) {
                if (w[i] > mid) {
                    trips = T + 1;
                    break;
                }
                if (current_weight + w[i] <= mid) {
                    current_weight += w[i];
                } else {
                    trips++;
                    current_weight = w[i];
                }
                if (trips > T) {
                    break;
                }
            }
            
            if (trips <= T) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
