#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned int a, b;
    while (cin >> a >> b && (a || b)) {
        int count = 0;
        int carry = 0;
        while (a > 0 || b > 0) {
            int sum = a % 10 + b % 10 + carry;
            carry = sum / 10;
            if (carry > 0) {
                count++;
            }
            a /= 10;
            b /= 10;
        }
        
        if (count == 0) {
            cout << "No carry operation.\n";
        } else if (count == 1) {
            cout << "1 carry operation.\n";
        } else {
            cout << count << " carry operations.\n";
        }
    }
    
    return 0;
}
