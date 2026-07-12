#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    while (cin >> n >> m) {
        if (m == 0) {
            cout << "OK!\n";
        } else {
            long long r = n % m;
            if (r == 0) {
                cout << "OK!\n";
            } else {
                cout << r << "\n";
            }
        }
    }
    
    return 0;
}
