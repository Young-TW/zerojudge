#include <iostream>
#include <string>

using namespace std;

int to_int(const string& s) {
    if (s == "一") return 1;
    if (s == "二") return 2;
    if (s == "三") return 3;
    if (s == "四") return 4;
    if (s == "五") return 5;
    if (s == "六") return 6;
    if (s == "七") return 7;
    if (s == "八") return 8;
    if (s == "九") return 9;
    if (s == "十") return 10;
    return -1;
}

string to_chinese(int n) {
    switch (n) {
        case 2: return "二";
        case 3: return "三";
        case 4: return "四";
        case 5: return "五";
        case 6: return "六";
        case 7: return "七";
        case 8: return "八";
        case 9: return "九";
        case 10: return "十";
        case 11: return "十一";
        case 12: return "十二";
        case 13: return "十三";
        case 14: return "十四";
        case 15: return "十五";
        case 16: return "十六";
        case 17: return "十七";
        case 18: return "十八";
        case 19: return "十九";
        case 20: return "二十";
        default: return "";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    while (getline(cin, line)) {
        string s = "";
        for (char c : line) {
            if (c != ' ' && c != '\t' && c != '\r') {
                s += c;
            }
        }
        
        string c1, c2, c3;
        bool valid = false;
        
        if (s.length() == 9) { // UTF-8
            c1 = s.substr(0, 3);
            c2 = s.substr(3, 3);
            c3 = s.substr(6, 3);
            valid = true;
        } else if (s.length() == 6) { // Big5
            c1 = s.substr(0, 2);
            c2 = s.substr(2, 2);
            c3 = s.substr(4, 2);
            valid = true;
        }
        
        if (valid) {
            if (c2 == "有" || c2 == "又") {
                int a = to_int(c1);
                int b = to_int(c3);
                if (a != -1 && b != -1) {
                    cout << to_chinese(a + b) << "\n";
                    continue;
                }
            }
        }
        cout << "謬\n";
    }
    return 0;
}
