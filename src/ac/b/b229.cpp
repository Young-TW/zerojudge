#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int n;
        if (ss >> n) {
            unsigned long long fn;
            if (n <= 0) {
                fn = 1;
            } else if (n == 1) {
                fn = 3;
            } else {
                unsigned long long f0 = 1, f1 = 3;
                for (int i = 2; i <= n; i++) {
                    fn = 2 * f1 + f0;
                    f0 = f1;
                    f1 = fn;
                }
            }
            cout << fn << "\n";
        } else {
            cout << "\n";
        }
    }
    return 0;
}
