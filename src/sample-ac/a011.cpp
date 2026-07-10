#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        int cnt = 0;
        bool inWord = false;
        for (char c : line) {
            bool isLetter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
            if (isLetter) {
                if (!inWord) {
                    cnt++;
                    inWord = true;
                }
            } else {
                inWord = false;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}
