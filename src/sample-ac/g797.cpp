#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long K;
    while (cin >> N >> K) {
        vector<int> a(N);
        for (int i = 0; i < N; i++) cin >> a[i];
        
        int half = N / 2;
        // f[i] = 新位置 i 的牌來自舊位置 f[i]
        vector<int> f(N);
        for (int i = 0; i < N; i++) {
            if ((i & 1) == 0) f[i] = i / 2;
            else f[i] = half + i / 2;
        }
        
        vector<int> result(N);
        vector<char> visited(N, 0);
        
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                vector<int> cycle;
                int cur = i;
                while (!visited[cur]) {
                    visited[cur] = 1;
                    cycle.push_back(cur);
                    cur = f[cur];
                }
                int len = (int)cycle.size();
                long long kk = K % len;
                int shift = (int)kk;
                for (int j = 0; j < len; j++) {
                    int target = cycle[(j + shift) % len];
                    result[cycle[j]] = a[target];
                }
            }
        }
        
        for (int i = 0; i < N; i++) {
            cout << result[i];
            if (i + 1 < N) cout << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
