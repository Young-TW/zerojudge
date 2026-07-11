#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long C, R;
        cin >> C >> R;

        if (R == 0) {
            cout << "٩(ˊᗜˋ*)و\n";
            continue;
        }

        if (C == 0) {
            cout << "1\n";
            continue;
        }

        long long K;
        if (C >= R) {
            K = 2 * R - 1;
        } else {
            K = 2 * C;
        }

        cout << K << '\n';
    }

    return 0;
}
