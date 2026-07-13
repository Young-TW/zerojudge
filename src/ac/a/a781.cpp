#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    bool first = true;
    while (cin >> n && n > 0) {
        if (!first) {
            cout << "\n";
        }
        first = false;
        
        for (int i = 0; i < 8; ++i) {
            string row = "";
            for (int j = 0; j < 8; ++j) {
                if ((i + j) % 2 == 0) {
                    row += string(n, '#');
                } else {
                    row += string(n, '.');
                }
            }
            for (int k = 0; k < n; ++k) {
                cout << row << "\n";
            }
        }
    }
    
    return 0;
}
