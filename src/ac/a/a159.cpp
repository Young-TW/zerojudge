#include <iostream>
#include <string>
using namespace std;

int digitSum(int x) {
    int s = 0;
    while (x) { s += x % 10; x /= 10; }
    return s;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    while (n--) {
        string a, b, c, d;
        if (!(cin >> a >> b >> c >> d)) break;
        string s = a + b + c + d;
        int sum = 0;
        for (int i = 0; i < 16; i++) {
            int v = s[i] - '0';
            if (i % 2 == 0) {
                int dv = v * 2;
                sum += digitSum(dv);
            } else {
                sum += v;
            }
        }
        if (sum % 10 == 0) cout << "Valid\n";
        else cout << "Invalid\n";
    }
    return 0;
}
