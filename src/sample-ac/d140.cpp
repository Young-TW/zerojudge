#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        long long dollars = 0;
        long long cents = 0;
        size_t dot = s.find('.');
        
        if (dot == string::npos) {
            dollars = stoll(s);
            cents = 0;
        } else {
            if (dot > 0) {
                dollars = stoll(s.substr(0, dot));
            }
            string c = s.substr(dot + 1);
            if (c.length() >= 1) {
                cents += (c[0] - '0') * 10;
            }
            if (c.length() >= 2) {
                cents += (c[1] - '0');
            }
        }
        
        long long P = dollars * 100 + cents;
        long long discounted;
        
        if (P <= 10000) {
            discounted = P * 9 / 10;
        } else if (P <= 50000) {
            discounted = P * 8 / 10;
        } else {
            discounted = P * 6 / 10;
        }
        
        if (P < 10000) {
            discounted += 800;
        }
        
        long long d = discounted / 100;
        long long c = discounted % 100;
        
        cout << "$" << d << ".";
        if (c < 10) {
            cout << "0";
        }
        cout << c << "\n";
    }
    
    return 0;
}
