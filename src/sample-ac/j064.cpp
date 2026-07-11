#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N, M;
            cin >> N >> M;
            vector<int> counts(N + 1, 0);
            for (int i = 0; i < M; ++i) {
                for (int j = 1; j <= N; ++j) {
                    int priority;
                    cin >> priority;
                    if (priority == 1) {
                        counts[j]++;
                    }
                }
            }
            long long ans = 1;
            for (int j = 1; j <= N; ++j) {
                if (counts[j] > 0) {
                    ans *= counts[j];
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
