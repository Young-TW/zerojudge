#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, d;
    while (cin >> m >> d) {
        int date = m * 100 + d;
        if (date >= 321 && date <= 420) {
            cout << "Aries\n";
        } else if (date >= 421 && date <= 521) {
            cout << "Taurus\n";
        } else if (date >= 522 && date <= 621) {
            cout << "Gemini\n";
        } else if (date >= 622 && date <= 722) {
            cout << "Cancer\n";
        } else if (date >= 723 && date <= 821) {
            cout << "Leo\n";
        } else if (date >= 822 && date <= 923) {
            cout << "Virgo\n";
        } else if (date >= 924 && date <= 1023) {
            cout << "Libra\n";
        } else if (date >= 1024 && date <= 1122) {
            cout << "Scorpio\n";
        } else if (date >= 1123 && date <= 1222) {
            cout << "Sagittarius\n";
        } else if (date >= 1223 || date <= 120) {
            cout << "Capricorn\n";
        } else if (date >= 121 && date <= 219) {
            cout << "Aquarius\n";
        } else if (date >= 220 && date <= 320) {
            cout << "Pisces\n";
        }
    }
    
    return 0;
}
