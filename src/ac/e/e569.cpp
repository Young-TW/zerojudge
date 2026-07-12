#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int main() {
    vector<string> wordList;
    string line;

    while (getline(cin, line)) {
        if (line == "0") break;

        string current;
        for (size_t i = 0; i < line.size(); ++i) {
            if (isalpha(line[i])) {
                current += line[i];
            } else {
                if (!current.empty()) {
                    bool found = false;
                    for (size_t j = 0; j < wordList.size(); ++j) {
                        if (wordList[j] == current) {
                            cout << j + 1;
                            wordList.erase(wordList.begin() + j);
                            wordList.insert(wordList.begin(), current);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << current;
                        wordList.insert(wordList.begin(), current);
                    }
                    current.clear();
                }
                if (isdigit(line[i])) {
                    int num = 0;
                    while (i < line.size() && isdigit(line[i])) {
                        num = num * 10 + (line[i] - '0');
                        ++i;
                    }
                    --i;
                    if (num > 0 && num <= static_cast<int>(wordList.size())) {
                        string word = wordList[num - 1];
                        cout << word;
                        wordList.erase(wordList.begin() + num - 1);
                        wordList.insert(wordList.begin(), word);
                    }
                } else {
                    cout << line[i];
                }
            }
        }
        if (!current.empty()) {
            bool found = false;
            for (size_t j = 0; j < wordList.size(); ++j) {
                if (wordList[j] == current) {
                    cout << j + 1;
                    wordList.erase(wordList.begin() + j);
                    wordList.insert(wordList.begin(), current);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << current;
                wordList.insert(wordList.begin(), current);
            }
        }
        cout << endl;
    }

    return 0;
}
