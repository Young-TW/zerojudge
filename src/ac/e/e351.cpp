#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long a, b;
    while (cin >> a >> b) {
        if (a > b) {
            swap(a, b);
        }
        while (a < b) {
            b &= (b - 1);
        }
        cout << b << "\n";
    }
    
    return 0;
}
