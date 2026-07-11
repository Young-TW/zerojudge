#include <iostream>
#include <string>
#include <set>
#include <cctype>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    set<string> dict;
    string line;
    while (getline(cin, line)) {
        string word;
        for (size_t i = 0; i < line.size(); ++i) {
            unsigned char c = (unsigned char)line[i];
            if (isalpha(c)) {
                word += (char)tolower(c);
            } else {
                if (!word.empty()) {
                    dict.insert(word);
                    word.clear();
                }
            }
        }
        if (!word.empty()) {
            dict.insert(word);
            word.clear();
        }
    }
    for (set<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        cout << *it << "\n";
    }
    return 0;
}
