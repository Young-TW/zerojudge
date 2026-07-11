#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        int p;
        cin >> p;
        int max_p = p;
        for (int i = 1; i < n; ++i) {
            cin >> p;
            if (p > max_p) {
                max_p = p;
            }
        }
        cout << max_p << '\n';
    }
    
    return 0;
}
