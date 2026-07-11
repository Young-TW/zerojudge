#include <iostream>
#include <string>

using namespace std;

bool is_prime(int n) {
    if (n == 1) return true;
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int sum = 0;
        for (char c : s) {
            if (c >= 'a' && c <= 'z') {
                sum += c - 'a' + 1;
            } else if (c >= 'A' && c <= 'Z') {
                sum += c - 'A' + 27;
            }
        }
        if (is_prime(sum)) {
            cout << "It is a prime word.\n";
        } else {
            cout << "It is not a prime word.\n";
        }
    }
    
    return 0;
}
