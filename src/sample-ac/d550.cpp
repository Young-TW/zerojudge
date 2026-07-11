#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<long long>> arr(N, vector<long long>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> arr[i][j];
            }
        }
        sort(arr.begin(), arr.end());
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (j > 0) cout << ' ';
                cout << arr[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
