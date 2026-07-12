#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string token;
    int count = 0;
    while (cin >> token) {
        bool hasAlnum = false;
        for (size_t i = 0; i < token.size(); ++i) {
            if (isalnum((unsigned char)token[i])) {
                hasAlnum = true;
                break;
            }
        }
        if (hasAlnum) ++count;
    }
    cout << count << "\n";
    return 0;
}
