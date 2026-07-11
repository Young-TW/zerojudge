#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<long long> s(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            cin >> s[i];
            s[i] += s[i - 1];
        }
        
        int M, L, C;
        cin >> M >> L >> C;
        
        const long long NEG = LLONG_MIN / 4;
        
        vector<long long> g(N + 1, NEG), newg(N + 1, NEG);
        
        long long ans = 0;
        
        for (int j = 1; j <= M; j++) {
            newg[0] = NEG;
            
            for (int i = 1; i <= N; i++) {
                int end = min(i + L - 1, N);
                long long fi = s[end] - s[i - 1];
                
                long long val;
                if (j == 1) {
                    val = fi;
                } else {
                    int prev_idx = i - L - C;
                    if (prev_idx >= 1 && g[prev_idx] > NEG) {
                        val = fi + g[prev_idx];
                    } else {
                        val = NEG;
                    }
                }
                
                newg[i] = max(newg[i - 1], val);
            }
            
            swap(g, newg);
            ans = max(ans, g[N]);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
