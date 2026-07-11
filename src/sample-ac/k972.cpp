#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        if ((n & (n + 1)) == 0) {
            cout << "Bob\n";
        } else {
            cout << "Alice\n";
        }
    }
    
    return 0;
}
