#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    while (cin >> n >> m >> k) {
        if (n == 0 && m == 0 && k == 0) break;
        
        if (m % 2 == 1) {
            cout << "Keka\n";
        } else {
            cout << "Gared\n";
        }
    }
    
    return 0;
}
