#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int X, Y;
    while (cin >> X >> Y) {
        vector<int> A(X);
        vector<int> B(Y);
        for (int i = 0; i < X; ++i) {
            cin >> A[i];
        }
        for (int i = 0; i < Y; ++i) {
            cin >> B[i];
        }
        
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        
        long long W = 0, L = 0;
        for (int i = 0; i < X; ++i) {
            long long w_a = lower_bound(B.begin(), B.end(), A[i]) - B.begin();
            long long l_a = B.end() - upper_bound(B.begin(), B.end(), A[i]);
            W += w_a;
            L += l_a;
        }
        
        bool found = false;
        for (int i = 0; i < X; ++i) {
            long long w_a = lower_bound(B.begin(), B.end(), A[i]) - B.begin();
            long long l_a = B.end() - upper_bound(B.begin(), B.end(), A[i]);
            if (l_a <= w_a && L + l_a < W + w_a) {
                cout << A[i] << "\n";
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << -1 << "\n";
        }
    }
    
    return 0;
}
