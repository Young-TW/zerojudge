#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    
    char var = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') { var = s[i]; break; }
    }
    
    double coef = 0, constv = 0;
    int sign = 1, side = 1;
    int i = 0, n = (int)s.size();
    
    while (i < n) {
        char c = s[i];
        if (c == '=') { side = -1; sign = 1; i++; continue; }
        if (c == '+') { sign = 1; i++; continue; }
        if (c == '-') { sign = -1; i++; continue; }
        if (c >= 'a' && c <= 'z') {
            coef += (double)side * sign;
            i++;
            continue;
        }
        if (c >= '0' && c <= '9') {
            int num = 0;
            while (i < n && s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            if (i < n && s[i] >= 'a' && s[i] <= 'z') {
                coef += (double)side * sign * num;
                i++;
            } else {
                constv += (double)side * sign * num;
            }
            continue;
        }
        i++;
    }
    
    double result = -constv / coef;
    if (fabs(result) < 0.0005) result = 0;
    
    cout << var << "＝" << fixed << setprecision(3) << result << "\n";
    return 0;
}
