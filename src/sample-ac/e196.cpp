#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<int> count(N + 1, 0);
        for (int i = 0; i < M; ++i) {
            int x;
            cin >> x;
            if (x >= 1 && x <= N) {
                count[x]++;
            }
        }
        
        int ans = 0;
        for (int i = 1; i <= N; ++i) {
            if (count[i] < 2) {
                ans++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
