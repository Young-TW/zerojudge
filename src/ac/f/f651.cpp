#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n) {
        cout << (n + 2) / 3 << "\n";
    }
    
    return 0;
}
