#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        int M;
        cin >> M;
        vector<int> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        for (int i = 0; i < M; ++i) {
            next_permutation(arr.begin(), arr.end());
        }
        for (int i = 0; i < N; ++i) {
            cout << arr[i] << (i == N - 1 ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}
