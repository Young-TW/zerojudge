#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned int n;
    while (cin >> n) {
        unsigned int b1 = (n >> 24) & 0xFF;
        unsigned int b2 = (n >> 16) & 0xFF;
        unsigned int b3 = (n >> 8) & 0xFF;
        unsigned int b4 = n & 0xFF;
        cout << b1 << "." << b2 << "." << b3 << "." << b4 << "\n";
    }
    
    return 0;
}
