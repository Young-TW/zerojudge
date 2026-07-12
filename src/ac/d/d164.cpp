#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        if (M > N) {
            M = N;
        }
        
        vector<int> arr(2 * N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
            arr[i + N] = arr[i];
        }
        
        long long sum = 0;
        for (int i = 0; i < M; ++i) {
            sum += arr[i];
        }
        
        long long max_sum = sum;
        for (int i = M; i < 2 * N; ++i) {
            sum += arr[i] - arr[i - M];
            if (sum > max_sum) {
                max_sum = sum;
            }
        }
        
        cout << max_sum << "\n";
    }
    
    return 0;
}
