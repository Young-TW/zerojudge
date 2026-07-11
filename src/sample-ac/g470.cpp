#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long low, high;
    while (cin >> low >> high) {
        if (low == 0 && high == 0) {
            break;
        }
        cout << 1 + high / 5 - low / 5 << "\n";
    }
    
    return 0;
}
