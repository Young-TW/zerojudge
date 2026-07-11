#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    int c[9];
    while (cin >> c[0] >> c[1] >> c[2] >> c[3] >> c[4] >> c[5] >> c[6] >> c[7] >> c[8]) {
        string ans = "";
        bool first = true;
        for (int i = 0; i < 9; ++i) {
            int coeff = c[i];
            if (coeff == 0) continue;
            int exp = 8 - i;
            
            if (first) {
                if (coeff < 0) ans += "-";
                if (abs(coeff) != 1 || exp == 0) {
                    ans += to_string(abs(coeff));
                }
                first = false;
            } else {
                if (coeff < 0) ans += " - ";
                else ans += " + ";
                if (abs(coeff) != 1 || exp == 0) {
                    ans += to_string(abs(coeff));
                }
            }
            
            if (exp > 1) {
                ans += "x^" + to_string(exp);
            } else if (exp == 1) {
                ans += "x";
            }
        }
        if (first) {
            ans = "0";
        }
        cout << ans << endl;
    }
    return 0;
}
