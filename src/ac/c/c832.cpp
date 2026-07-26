#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        while (T--) {
            int a1, a2, b1, b2, c1, c2;
            cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2;
            
            int A[2] = {a1, a2};
            int B[2] = {b1, b2};
            int C[2] = {c1, c2};
            
            bool ok = false;
            for (int i = 0; i < 2 && !ok; ++i) {
                for (int j = 0; j < 2 && !ok; ++j) {
                    for (int k = 0; k < 2 && !ok; ++k) {
                        if (A[i] != B[j] && A[i] != C[k] && B[j] != C[k]) {
                            ok = true;
                        }
                    }
                }
            }
            
            cout << (ok ? "Yes" : "No") << "\n";
        }
    }
    
    return 0;
}
