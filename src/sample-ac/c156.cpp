#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long L;
    int N, M;
    
    while (cin >> L >> N >> M) {
        vector<long long> d(N + 2);
        d[0] = 0;
        for (int i = 1; i <= N; ++i) {
            cin >> d[i];
        }
        d[N + 1] = L;
        
        long long l = 1, r = L;
        long long ans = 0;
        
        while (l <= r) {
            long long mid = l + (r - l) / 2;
            int cnt = 0;
            long long last = 0;
            
            for (int i = 1; i <= N; ++i) {
                if (d[i] - last < mid) {
                    cnt++;
                } else {
                    last = d[i];
                }
            }
            if (d[N + 1] - last < mid) {
                cnt++;
            }
            
            if (cnt <= M) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
