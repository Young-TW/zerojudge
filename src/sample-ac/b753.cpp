#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        int T = 0, O = 0, F = 0;
        unordered_set<string> seen;
        const int letterMap[26] = {10,11,12,13,14,15,16,17,34,18,19,20,21,22,35,23,24,25,26,27,28,29,32,30,31,33};
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            if (s.size() != 10) { F++; continue; }
            char c = s[0];
            if (c < 'A' || c > 'Z') { F++; continue; }
            bool ok = true;
            for (int j = 1; j < 10; j++) {
                if (s[j] < '0' || s[j] > '9') { ok = false; break; }
            }
            if (!ok) { F++; continue; }
            int v = letterMap[c - 'A'];
            int n1 = v / 10;
            int n2 = v % 10;
            int n3 = s[1] - '0';
            if (n3 != 1 && n3 != 2) { F++; continue; }
            int n4 = s[2] - '0';
            int n5 = s[3] - '0';
            int n6 = s[4] - '0';
            int n7 = s[5] - '0';
            int n8 = s[6] - '0';
            int n9 = s[7] - '0';
            int n10 = s[8] - '0';
            int n11 = s[9] - '0';
            int sum = n1*1 + n2*9 + n3*8 + n4*7 + n5*6 + n6*5 + n7*4 + n8*3 + n9*2 + n10*1 + n11*1;
            if (sum % 10 != 0) { F++; continue; }
            if (seen.count(s)) {
                O++;
            } else {
                seen.insert(s);
                T++;
            }
        }
        cout << T << "," << O << "," << F << "\n";
    }
    return 0;
}
