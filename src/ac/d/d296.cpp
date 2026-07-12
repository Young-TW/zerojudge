#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long n;
    while (cin >> n) {
        cout << n * n * n << '\n';
    }
    
    return 0;
}
