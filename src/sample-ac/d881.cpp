#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long d;
    while (cin >> d) {
        cout << 1275 + 19600 * d << '\n';
    }
    
    return 0;
}
