#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    bool first = true;
    int catalan[11] = {0, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796};
    
    while (cin >> n) {
        if (!first) {
            cout << "\n";
        }
        first = false;
        cout << catalan[n] << "\n";
    }
    
    return 0;
}
