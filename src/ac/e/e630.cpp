#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<string, long long> digit;
    digit["零"] = 0; digit["一"] = 1; digit["二"] = 2; digit["三"] = 3;
    digit["四"] = 4; digit["五"] = 5; digit["六"] = 6; digit["七"] = 7;
    digit["八"] = 8; digit["九"] = 9;
    
    map<string, long long> unit;
    unit["十"] = 10; unit["百"] = 100; unit["千"] = 1000;
    unit["萬"] = 10000; unit["億"] = 100000000LL; unit["兆"] = 1000000000000LL;
    
    string s;
    while (cin >> s) {
        long long total = 0;
        long long section = 0;
        long long cur = 0;
        bool hasDigit = false;
        
        for (size_t i = 0; i + 3 <= s.size(); i += 3) {
            string c = s.substr(i, 3);
            if (digit.count(c)) {
                cur = digit[c];
                hasDigit = true;
            } else if (unit.count(c)) {
                long long u = unit[c];
                if (u >= 10000) {
                    if (hasDigit) {
                        section += cur;
                        cur = 0;
                        hasDigit = false;
                    }
                    total += section * u;
                    section = 0;
                } else {
                    if (!hasDigit) {
                        section += u;
                    } else {
                        section += cur * u;
                        cur = 0;
                        hasDigit = false;
                    }
                }
            }
        }
        if (hasDigit) {
            section += cur;
        }
        total += section;
        cout << total << '\n';
    }
    return 0;
}
