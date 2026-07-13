#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < n - i; ++j) cout << ' ';
            for (int j = 0; j < i; ++j) {
                cout << '*';
                if (j < i - 1) cout << ' ';
            }
            cout << '\n';
        }
        
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n - 2; ++j) cout << ' ';
            cout << "| |\n";
        }
        
        cout << '\\';
        for (int i = 0; i < 2 * n - 3; ++i) cout << '_';
        cout << "/\n";
    }
    
    return 0;
}
