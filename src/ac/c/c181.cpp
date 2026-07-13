#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<long long> a(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> a[i];
        }
        vector<char> isX(N + 1, 0);
        for (int i = 0; i < N / 2; ++i) {
            int b;
            cin >> b;
            isX[b] = 1;
        }
        
        long long totalY = 0;
        for (int i = 1; i <= N; ++i) {
            if (!isX[i]) totalY += a[i];
        }
        
        priority_queue<long long> pq;
        long long winSum = 0;
        for (int p = N; p >= 1; --p) {
            if (isX[p]) {
                if (!pq.empty()) {
                    winSum += pq.top();
                    pq.pop();
                }
            } else {
                pq.push(a[p]);
            }
        }
        
        long long ans = 2 * winSum - totalY;
        cout << ans << '\n';
    }
    
    return 0;
}
