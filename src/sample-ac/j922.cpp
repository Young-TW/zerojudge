#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    while (getline(cin, s)) {
        // 1. 句首大寫，其餘小寫
        string s1 = s;
        bool firstLetter = true;
        for (char &c : s1) {
            if (isalpha((unsigned char)c)) {
                if (firstLetter) {
                    c = toupper((unsigned char)c);
                    firstLetter = false;
                } else {
                    c = tolower((unsigned char)c);
                }
            }
        }
        cout << s1 << "\n";

        // 2. 全大寫
        string s2 = s;
        for (char &c : s2) {
            c = toupper((unsigned char)c);
        }
        cout << s2 << "\n";

        // 3. 標題大小寫（每個單字字首大寫，其餘小寫）
        string s3 = s;
        bool newWord = true;
        for (char &c : s3) {
            if (isalpha((unsigned char)c)) {
                if (newWord) {
                    c = toupper((unsigned char)c);
                    newWord = false;
                } else {
                    c = tolower((unsigned char)c);
                }
            } else {
                newWord = true;
            }
        }
        cout << s3 << "\n";

        // 4. 全小寫
        string s4 = s;
        for (char &c : s4) {
            c = tolower((unsigned char)c);
        }
        cout << s4 << "\n";
    }

    return 0;
}
