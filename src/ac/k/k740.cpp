#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        int arr[25] = {1};
        for (int i = 1; i <= n; ++i) {
            for (int j = i - 1; j >= 1; --j) {
                arr[j] += arr[j - 1];
            }
            for (int j = 0; j < i; ++j) {
                if (j > 0) cout << ' ';
                cout << arr[j];
            }
            cout << '\n';
        }
    }
    return 0;
}
