#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M) {
        vector<int> B(M + 1, 0);
        for (int i = 1; i <= N; ++i) {
            int a;
            cin >> a;
            if (a != 0) {
                B[a] = i;
            }
        }
        for (int i = 1; i <= M; ++i) {
            cout << B[i] << (i == M ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
