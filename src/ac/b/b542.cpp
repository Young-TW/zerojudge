#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    while (cin >> N >> Q) {
        vector<long long> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end());
        
        for (int q = 0; q < Q; ++q) {
            long long K;
            cin >> K;
            bool found = false;
            int i = 0, j = 1;
            while (j < N) {
                long long diff = arr[j] - arr[i];
                if (diff == K) {
                    found = true;
                    break;
                } else if (diff < K) {
                    j++;
                } else {
                    i++;
                    if (i == j) {
                        j++;
                    }
                }
            }
            cout << (found ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}
