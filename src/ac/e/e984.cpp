#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int K;
    while (cin >> K) {
        queue<long long> q;
        for (int i = 1; i <= 9; ++i) {
            q.push(i);
        }
        
        long long ans = 0;
        for (int i = 0; i < K; ++i) {
            ans = q.front();
            q.pop();
            int last = ans % 10;
            if (last > 0) {
                q.push(ans * 10 + (last - 1));
            }
            q.push(ans * 10 + last);
            if (last < 9) {
                q.push(ans * 10 + (last + 1));
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
