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
            int N, W;
            cin >> N >> W;
            vector<int> arr(N);
            vector<long long> pref(N + 1, 0);
            for (int i = 0; i < N; ++i) {
                cin >> arr[i];
                pref[i + 1] = pref[i] + arr[i];
            }
            
            for (int i = 0; i < W; ++i) {
                int K;
                cin >> K;
                if (K == 1) {
                    int X, Y;
                    cin >> X >> Y;
                    cout << *max_element(arr.begin() + X, arr.begin() + Y + 1) << "\n";
                } else if (K == 2) {
                    int X, Y;
                    cin >> X >> Y;
                    long long sum = pref[Y + 1] - pref[X];
                    long long len = Y - X + 1;
                    cout << sum / len << "\n";
                } else if (K == 3) {
                    int E;
                    cin >> E;
                    cout << arr[E] << "\n";
                }
            }
        }
    }
    return 0;
}
