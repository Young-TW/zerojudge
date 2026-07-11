#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    char C;
    while (cin >> N >> M >> C) {
        for (int i = 0; i < N; ++i) {
            unsigned long long S;
            cin >> S;
            for (int j = M - 1; j >= 0; --j) {
                if ((S >> j) & 1ULL) {
                    cout << C;
                } else {
                    cout << '.';
                }
                if (j > 0) {
                    cout << ' ';
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
