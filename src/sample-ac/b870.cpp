#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N, K;
            cin >> N >> K;
            vector<long long> trees(N);
            for (int i = 0; i < N; ++i) {
                cin >> trees[i];
            }
            sort(trees.begin(), trees.end());
            
            long long low = 0, high = 1000000000LL;
            while (low < high) {
                long long mid = low + (high - low) / 2;
                int count = 0;
                int i = 0;
                while (i < N) {
                    count++;
                    long long cover_up_to = trees[i] + 2 * mid;
                    while (i < N && trees[i] <= cover_up_to) {
                        i++;
                    }
                }
                if (count <= K) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            cout << low << "\n";
        }
    }
    return 0;
}
