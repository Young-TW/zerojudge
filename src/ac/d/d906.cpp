#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

struct Student {
    char name;
    int id;
    int h;
};

int main() {
    string tok;
    bool firstOutput = true;
    while (cin >> tok) {
        string label;
        if (tok == "輸入範例一") {
            label = "輸出範例一";
            if (!(cin >> tok)) break;
        } else if (tok == "輸入範例二") {
            label = "輸出範例二";
            if (!(cin >> tok)) break;
        }
        bool numeric = true;
        for (size_t i = 0; i < tok.size(); i++) {
            if (!isdigit((unsigned char)tok[i])) { numeric = false; break; }
        }
        if (!numeric) continue;
        
        int m = stoi(tok);
        int n;
        cin >> n;
        vector<Student> s(6);
        for (int i = 0; i < 6; i++) {
            cin >> s[i].name >> s[i].id >> s[i].h;
        }
        if (m % 2 == 1) {
            sort(s.begin(), s.end(), [](const Student&a, const Student&b){ return a.id < b.id; });
        } else {
            sort(s.begin(), s.end(), [](const Student&a, const Student&b){ 
                if (a.h != b.h) return a.h < b.h;
                return a.id < b.id;
            });
        }
        int idx = ((2 - n) % 6 + 6) % 6;
        
        if (!label.empty()) {
            if (!firstOutput) cout << "\n\n";
            cout << label << "\n";
        } else {
            if (!firstOutput) cout << "\n";
        }
        firstOutput = false;
        cout << s[idx].name << "\n";
    }
    return 0;
}
