#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        string word;
        for (size_t i = 0; i < line.length(); ++i) {
            if (isspace(static_cast<unsigned char>(line[i]))) {
                if (!word.empty()) {
                    reverse(word.begin(), word.end());
                    cout << word;
                    word.clear();
                }
                cout << line[i];
            } else {
                word += line[i];
            }
        }
        if (!word.empty()) {
            reverse(word.begin(), word.end());
            cout << word;
        }
        cout << "\n";
    }
    
    return 0;
}
