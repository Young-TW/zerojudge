#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        if (n != m) {
            cout << ">\\\\\\<\n";
        } else {
            cout << "= =\"\n";
        }
    }
    
    return 0;
}
