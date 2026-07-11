#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        if (b != c) {
            cout << "Error\n";
            continue;
        }
        
        vector<long long> A(a * b);
        for (int i = 0; i < a * b; ++i) {
            cin >> A[i];
        }
        
        vector<long long> B(c * d);
        for (int i = 0; i < c * d; ++i) {
            cin >> B[i];
        }
        
        vector<long long> C(a * d, 0);
        for (int i = 0; i < a; ++i) {
            for (int k = 0; k < b; ++k) {
                long long r = A[i * b + k];
                for (int j = 0; j < d; ++j) {
                    C[i * d + j] += r * B[k * d + j];
                }
            }
        }
        
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < d; ++j) {
                cout << C[i * d + j];
                if (j == d - 1) {
                    cout << '\n';
                } else {
                    cout << ' ';
                }
            }
        }
    }
    
    return 0;
}
