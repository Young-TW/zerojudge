#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int w;
    while (cin >> w) {
        if (w > 50) {
            cout << w - 1 << "\n";
        } else {
            cout << w << "\n";
        }
    }
    
    return 0;
}
