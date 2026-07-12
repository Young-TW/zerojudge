#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<int> pwd(M);
        for (int i = 0; i < M; ++i) {
            cin >> pwd[i];
        }
        
        for (int k = 0; k < N; ++k) {
            vector<long long> A(M + 1);
            for (int i = 0; i <= M; ++i) {
                cin >> A[i];
            }
            
            bool match = true;
            for (int i = 0; i < M; ++i) {
                int val;
                if (i == M - 1) {
                    val = (A[M] >= A[M-1]) ? 1 : 0;
                } else {
                    long long diff = A[i+1] - A[i+2];
                    if (diff < 0) diff = -diff;
                    val = (diff >= A[i]) ? 1 : 0;
                }
                if (val != pwd[i]) {
                    match = false;
                }
            }
            
            if (match) {
                for (int i = 0; i <= M; ++i) {
                    if (i > 0) cout << " ";
                    cout << A[i];
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
