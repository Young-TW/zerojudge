#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        while (n % 2 == 0) n /= 2;
        while (n % 3 == 0) n /= 3;
        while (n % 5 == 0) n /= 5;
        
        if (n == 1) {
            cout << "ugly\n";
        } else {
            cout << "beautiful\n";
        }
    }
    
    return 0;
}
