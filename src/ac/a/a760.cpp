#include <iostream>
#include <string>

using namespace std;

bool isValidDate(const string& s, int start, long long& val) {
    int year = (s[start] - '0') * 1000 + (s[start+1] - '0') * 100 + (s[start+2] - '0') * 10 + (s[start+3] - '0');
    int month = (s[start+4] - '0') * 10 + (s[start+5] - '0');
    int day = (s[start+6] - '0') * 10 + (s[start+7] - '0');
    int hour = (s[start+8] - '0') * 10 + (s[start+9] - '0');
    int minute = (s[start+10] - '0') * 10 + (s[start+11] - '0');
    int second = (s[start+12] - '0') * 10 + (s[start+13] - '0');
    
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;
    
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (isLeap) daysInMonth[2] = 29;
    
    if (day > daysInMonth[month]) return false;
    if (hour > 23) return false;
    if (minute > 59) return false;
    if (second > 59) return false;
    
    val = 0;
    for (int i = 0; i < 14; ++i) {
        val = val * 10 + (s[start+i] - '0');
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    long long target = 20130918133000LL;
    bool found = false;
    long long best = 0;
    
    while (getline(cin, line)) {
        string digits = "";
        for (char c : line) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                digits += (char)('0' + (c % 3));
            }
        }
        if (digits.length() < 14) continue;
        int len = digits.length();
        for (int i = 0; i <= len - 14; ++i) {
            long long val;
            if (isValidDate(digits, i, val)) {
                if (val > target) {
                    if (!found || val < best) {
                        found = true;
                        best = val;
                    }
                }
            }
        }
    }
    
    if (found) {
        string s = to_string(best);
        while (s.length() < 14) s = "0" + s;
        cout << s.substr(0, 4) << "/" << s.substr(4, 2) << "/" << s.substr(6, 2) << " "
             << s.substr(8, 2) << ":" << s.substr(10, 2) << ":" << s.substr(12, 2) << endl;
    }
    
    return 0;
}
