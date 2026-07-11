#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K, T;
    while (cin >> N >> K >> T) {
        vector<int> passed;
        for (int i = 0; i < N; ++i) {
            vector<int> scores(K);
            for (int j = 0; j < K; ++j) {
                cin >> scores[j];
            }
            sort(scores.begin(), scores.end());
            int sum = 0;
            for (int j = 1; j < K - 1; ++j) {
                sum += scores[j];
            }
            if (sum >= T * (K - 2)) {
                passed.push_back(i);
            }
        }
        if (passed.empty()) {
            cout << "A is for apple.\n";
        } else {
            for (int x : passed) {
                cout << x << "\n";
            }
        }
    }
    return 0;
}
