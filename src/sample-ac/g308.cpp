#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, T;
    while (cin >> N >> T) {
        vector<int> x(N);
        for (int i = 0; i < N; ++i) {
            cin >> x[i];
        }
        vector<int> y(N);
        for (int i = 0; i < N; ++i) {
            cin >> y[i];
        }
        
        vector<bool> visited(N, false);
        int curr = T;
        int ans = 0;
        
        while (!visited[curr]) {
            visited[curr] = true;
            ans += y[curr];
            curr = x[curr];
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
