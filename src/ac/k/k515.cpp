#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <unordered_set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_set<string> lower_words = {
        "a", "an", "the", "and", "but", "or", "for", "nor", 
        "on", "at", "to", "from", "by", "in", "of"
    };

    string line;
    while (getline(cin, line)) {
        for (char &c : line) {
            c = tolower(static_cast<unsigned char>(c));
        }

        stringstream ss(line);
        string word;
        vector<string> words;
        while (ss >> word) {
            words.push_back(word);
        }

        if (words.empty()) {
            cout << "\n";
            continue;
        }

        for (size_t i = 0; i < words.size(); ++i) {
            if (i == 0 || i == words.size() - 1) {
                if (!words[i].empty()) {
                    words[i][0] = toupper(static_cast<unsigned char>(words[i][0]));
                }
            } else {
                if (lower_words.find(words[i]) == lower_words.end()) {
                    if (!words[i].empty()) {
                        words[i][0] = toupper(static_cast<unsigned char>(words[i][0]));
                    }
                }
            }
        }

        for (size_t i = 0; i < words.size(); ++i) {
            if (i > 0) cout << " ";
            cout << words[i];
        }
        cout << "\n";
    }

    return 0;
}
