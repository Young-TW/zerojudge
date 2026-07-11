#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<long long> d(N), r(N);
        for (int i = 0; i < N; ++i) {
            cin >> d[i];
        }
        for (int i = 0; i < N; ++i) {
            cin >> r[i];
        }
        
        long long max_reach = 0;
        if (N > 0) {
            max_reach = d[0] + r[0];
            for (int i = 1; i < N; ++i) {
                if (d[i] <= max_reach) {
                    max_reach = max(max_reach, d[i] + r[i]);
                } else {
                    break;
                }
            }
        }
        
        cout << max_reach << "\n";
    }
    
    return 0;
}
