#include <iostream>
#include <string>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int D;
    while (cin >> D) {
        while (D--) {
            string s;
            cin >> s;
            bool isPrimeDay = true;
            for (int i = 0; i < 8; ++i) {
                int j = i;
                while (j < 8 && s[j] == '0') {
                    j++;
                }
                if (j == 8) {
                    isPrimeDay = false;
                    break;
                }
                int num = 0;
                for (int k = j; k < 8; ++k) {
                    num = num * 10 + (s[k] - '0');
                }
                if (!isPrime(num)) {
                    isPrimeDay = false;
                    break;
                }
            }
            if (isPrimeDay) {
                cout << s << " is a Prime Day!\n";
            } else {
                cout << s << " isn't a Prime Day!\n";
            }
        }
    }
    return 0;
}
