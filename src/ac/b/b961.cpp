#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long parseTime(const string& s) {
    long long total_ms = 0;
    int i = 0;
    int n = s.length();
    while (i < n) {
        long long num = 0;
        int decimal = 0;
        bool has_decimal = false;
        while (i < n && (s[i] >= '0' && s[i] <= '9' || s[i] == '.')) {
            if (s[i] == '.') {
                has_decimal = true;
            } else {
                if (has_decimal) {
                    decimal = decimal * 10 + (s[i] - '0');
                } else {
                    num = num * 10 + (s[i] - '0');
                }
            }
            i++;
        }
        if (i < n) {
            if (s[i] == 'm' && i + 1 < n && s[i+1] == 's') {
                total_ms += num;
                i += 2;
            } else if (s[i] == 'm') {
                if (i + 2 < n && s[i+1] == 'i' && s[i+2] == 'n') {
                    total_ms += num * 60000;
                    i += 3;
                } else {
                    total_ms += num * 60000;
                    i += 1;
                }
            } else if (s[i] == 's') {
                total_ms += num * 1000 + decimal * 100;
                i += 1;
            }
        }
    }
    return total_ms;
}

long long parseMemory(const string& s) {
    long long num = 0;
    int decimal = 0;
    bool has_decimal = false;
    int i = 0;
    int n = s.length();
    while (i < n && (s[i] >= '0' && s[i] <= '9' || s[i] == '.')) {
        if (s[i] == '.') {
            has_decimal = true;
        } else {
            if (has_decimal) {
                decimal = decimal * 10 + (s[i] - '0');
            } else {
                num = num * 10 + (s[i] - '0');
            }
        }
        i++;
    }
    if (i < n) {
        if (s[i] == 'K') { // KB
            return num;
        } else if (s[i] == 'M') { // MB
            return num * 1000 + decimal * 100;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string T1, M1, T2, M2;
    while (cin >> T1 >> M1 >> T2 >> M2) {
        string line;
        getline(cin, line); // 吃掉 M2 後面的換行符
        
        vector<string> user_output;
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line == "(This is the end of the user's output.)") {
                break;
            }
            user_output.push_back(line);
        }
        
        vector<string> correct_answer;
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line == "(This is the end of the correct answer.)") {
                break;
            }
            correct_answer.push_back(line);
        }
        
        if (parseTime(T1) > parseTime(T2)) {
            cout << "TLE\n";
        } else if (parseMemory(M1) > parseMemory(M2)) {
            cout << "MLE\n";
        } else if (user_output.size() > correct_answer.size()) {
            cout << "OLE\n";
        } else if (user_output != correct_answer) {
            cout << "WA\n";
        } else {
            cout << "AC\n";
        }
    }
    
    return 0;
}
