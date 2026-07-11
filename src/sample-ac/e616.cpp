#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, C;
    while (cin >> N >> C) {
        vector<long long> x(N);
        for (int i = 0; i < N; ++i) {
            cin >> x[i];
        }
        sort(x.begin(), x.end());
        
        long long left = 1;
        long long right = x[N - 1] - x[0];
        long long ans = 0;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            int count = 1;
            long long last_pos = x[0];
            
            for (int i = 1; i < N; ++i) {
                if (x[i] - last_pos >= mid) {
                    count++;
                    last_pos = x[i];
                }
            }
            
            if (count >= C) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
