#include <iostream>

using namespace std;

int ans_x[10005];
int ans_y[10005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i <= 10000; ++i) {
        ans_x[i] = -1;
    }

    for (int y = 1; y <= 100; ++y) {
        for (int x = y + 1; x <= 100; ++x) {
            int val = x * x * x - y * y * y;
            if (val > 10000) break;
            if (ans_x[val] == -1) {
                ans_x[val] = x;
                ans_y[val] = y;
            }
        }
    }

    int N;
    while (cin >> N && N) {
        if (ans_x[N] == -1) {
            cout << "No solution\n";
        } else {
            cout << ans_x[N] << " " << ans_y[N] << "\n";
        }
    }

    return 0;
}
