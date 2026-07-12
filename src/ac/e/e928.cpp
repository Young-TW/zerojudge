#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N1;
    while (cin >> N1) {
        vector<int> A(N1 + 1);
        for (int i = 0; i <= N1; ++i) {
            cin >> A[i];
        }

        int N2;
        cin >> N2;
        vector<int> B(N2 + 1);
        for (int i = 0; i <= N2; ++i) {
            cin >> B[i];
        }

        int M = N1 + N2;
        vector<int> C(M + 1, 0);

        for (int i = 0; i <= N1; ++i) {
            for (int j = 0; j <= N2; ++j) {
                C[i + j] += A[i] * B[j];
            }
        }

        cout << M << "\n";
        for (int i = 0; i <= M; ++i) {
            cout << C[i] << (i == M ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
