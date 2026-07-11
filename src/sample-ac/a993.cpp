#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n <= 1) {
            cout << 1 << '\n';
            continue;
        }
        
        int remainder = 1 % n;
        int count = 1;
        
        while (remainder != 0) {
            remainder = (remainder * 10 + 1) % n;
            count++;
        }
        
        cout << count << '\n';
    }
    
    return 0;
}
