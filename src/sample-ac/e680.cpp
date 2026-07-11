#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

string getZodiac(int m, int d) {
    int md = m * 100 + d;
    if (md >= 1222 || md <= 119) return "capricorn";
    if (md >= 1122) return "sagittarius";
    if (md >= 1023) return "scorpio";
    if (md >= 923) return "libra";
    if (md >= 823) return "virgo";
    if (md >= 723) return "leo";
    if (md >= 622) return "cancer";
    if (md >= 521) return "gemini";
    if (md >= 420) return "taurus";
    if (md >= 321) return "aries";
    if (md >= 219) return "pisces";
    return "aquarius";
}

int main() {
    int N;
    while (cin >> N) {
        for (int i = 1; i <= N; ++i) {
            string s;
            cin >> s;
            int m = (s[0] - '0') * 10 + (s[1] - '0');
            int d = (s[2] - '0') * 10 + (s[3] - '0');
            int y = (s[4] - '0') * 1000 + (s[5] - '0') * 100 + (s[6] - '0') * 10 + (s[7] - '0');
            
            int daysToAdd = 280;
            d += daysToAdd;
            while (true) {
                int dim = daysInMonth[m];
                if (m == 2 && isLeap(y)) dim = 29;
                if (d > dim) {
                    d -= dim;
                    m++;
                    if (m > 12) {
                        m = 1;
                        y++;
                    }
                } else {
                    break;
                }
            }
            
            printf("%d %02d/%02d/%04d %s\n", i, m, d, y, getZodiac(m, d).c_str());
        }
    }
    return 0;
}
