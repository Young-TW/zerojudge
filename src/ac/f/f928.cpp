#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> x(N);
        for (int i = 0; i < N; ++i) {
            cin >> x[i];
        }
        int T;
        cin >> T;
        
        queue<int> q;
        q.push(T);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (x[u] == 0) continue;
            
            int k = x[u];
            x[u] = 0;
            
            if (k == 1) {
                // 啞炮，只引爆自己
            } else if (k == 2) {
                // 左右炮
                if (u - 1 >= 0) q.push(u - 1);
                if (u + 1 < N) q.push(u + 1);
            } else {
                // 怪怪炮
                if (u - k >= 0) q.push(u - k);
                if (u - 2 * k >= 0) q.push(u - 2 * k);
                if (u + k < N) q.push(u + k);
                if (u + 2 * k < N) q.push(u + 2 * k);
            }
        }
        
        for (int i = 0; i < N; ++i) {
            cout << x[i] << (i == N - 1 ? '\n' : ' ');
        }
    }
    
    return 0;
}
