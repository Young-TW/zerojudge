#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        cout << N << " " << M << "\n";
        if (N == 0 && M == 0) break;
        
        vector<int> v(N);
        for (int i = 0; i < N; ++i) {
            cin >> v[i];
        }
        
        auto cmp = [M](int a, int b) {
            int ra = a % M;
            int rb = b % M;
            if (ra != rb) return ra < rb;
            
            bool a_odd = (a % 2 != 0);
            bool b_odd = (b % 2 != 0);
            
            if (a_odd != b_odd) return a_odd;
            if (a_odd) return a > b;
            return a < b;
        };
        
        sort(v.begin(), v.end(), cmp);
        
        for (int i = 0; i < N; ++i) {
            cout << v[i] << "\n";
        }
    }
    
    return 0;
}
