#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            int w;
            cin >> w;
            if (w <= 10) {
                count++;
            }
        }
        cout << count << "\n";
    }

    return 0;
}
