#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int sum[1001] = {0};
    for (int i = 1; i <= 500; ++i) {
        for (int j = i * 2; j <= 1000; j += i) {
            sum[j] += i;
        }
    }

    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            if (!(cin >> n)) break;
            if (sum[n] == n) {
                cout << "perfect\n";
            } else if (sum[n] < n) {
                cout << "deficient\n";
            } else {
                cout << "abundant\n";
            }
        }
    }
    
    int n;
    while (cin >> n) {
        if (sum[n] == n) {
            cout << "perfect\n";
        } else if (sum[n] < n) {
            cout << "deficient\n";
        } else {
            cout << "abundant\n";
        }
    }

    return 0;
}
