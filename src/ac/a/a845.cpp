#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        int A[200];
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        int T;
        cin >> T;
        for (int i = 0; i < T; ++i) {
            int x, y;
            cin >> x >> y;
            cout << A[x] + A[y] << '\n';
        }
    }
    
    return 0;
}
