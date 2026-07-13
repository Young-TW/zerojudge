#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long M;
    while (cin >> N >> M) {
        vector<int> trees(N);
        int max_h = 0;
        for (int i = 0; i < N; ++i) {
            cin >> trees[i];
            if (trees[i] > max_h) {
                max_h = trees[i];
            }
        }
        
        long long low = 0;
        long long high = max_h;
        long long ans = 0;
        
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            long long sum = 0;
            for (int i = 0; i < N; ++i) {
                if (trees[i] > mid) {
                    sum += trees[i] - mid;
                }
            }
            
            if (sum >= M) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
