#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            cout << a * (n - i) << ' ';
        }
        int a;
        cin >> a;
        cout << '\n';
    }
    
    return 0;
}
