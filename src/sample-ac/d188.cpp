#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int ans[50001][3];
    for (int i = 0; i <= 50000; ++i) {
        ans[i][0] = ans[i][1] = ans[i][2] = -1;
    }

    for (int a = 0; a <= 224; ++a) {
        for (int b = a; b <= 224; ++b) {
            for (int c = b; c <= 224; ++c) {
                int sum = a * a + b * b + c * c;
                if (sum > 50000) break;
                if (ans[sum][0] == -1) {
                    ans[sum][0] = a;
                    ans[sum][1] = b;
                    ans[sum][2] = c;
                }
            }
        }
    }

    int N;
    while (cin >> N) {
        while (N--) {
            int K;
            cin >> K;
            if (ans[K][0] == -1) {
                cout << "-1\n";
            } else {
                cout << ans[K][0] << " " << ans[K][1] << " " << ans[K][2] << "\n";
            }
        }
    }

    return 0;
}
