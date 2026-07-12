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
            vector<int> A(N);
            for (int i = 0; i < N; ++i) {
                cin >> A[i];
            }
            
            while (W--) {
                int K;
                cin >> K;
                if (K == 1) {
                    int X, Y;
                    cin >> X >> Y;
                    if (X > Y) swap(X, Y);
                    int max_val = A[X];
                    for (int i = X + 1; i <= Y; ++i) {
                        if (A[i] > max_val) {
                            max_val = A[i];
                        }
                    }
                    cout << max_val << "\n";
                } else if (K == 2) {
                    int X, Y;
                    cin >> X >> Y;
                    if (X > Y) swap(X, Y);
                    long long sum = 0;
                    for (int i = X; i <= Y; ++i) {
                        sum += A[i];
                    }
                    long long cnt = Y - X + 1;
                    cout << sum / cnt << "\n";
                } else if (K == 3) {
                    int E;
                    cin >> E;
                    cout << A[E] << "\n";
                }
            }
        }
    }
    
    return 0;
}
