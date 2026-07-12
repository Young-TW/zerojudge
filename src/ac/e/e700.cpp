#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, d;
    char slash;
    while (cin >> m >> slash >> d) {
        int val = m * 100 + d;
        if (val >= 1223 || val <= 120) {
            cout << "摩羯座\n";
        } else if (val >= 1123) {
            cout << "射手座\n";
        } else if (val >= 1024) {
            cout << "天蠍座\n";
        } else if (val >= 924) {
            cout << "天秤座\n";
        } else if (val >= 822) {
            cout << "處女座\n";
        } else if (val >= 723) {
            cout << "獅子座\n";
        } else if (val >= 622) {
            cout << "巨蟹座\n";
        } else if (val >= 522) {
            cout << "雙子座\n";
        } else if (val >= 421) {
            cout << "金牛座\n";
        } else if (val >= 321) {
            cout << "牡羊座\n";
        } else if (val >= 220) {
            cout << "雙魚座\n";
        } else if (val >= 121) {
            cout << "水瓶座\n";
        }
    }
    
    return 0;
}
