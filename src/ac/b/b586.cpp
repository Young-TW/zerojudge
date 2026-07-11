#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <cctype>

using namespace std;

int main() {
    list<string> wordList;
    unordered_map<string, list<string>::iterator> wordMap;
    string line;
    bool firstWord = true;

    while (getline(cin, line)) {
        if (line == "0") break;

        string word;
        for (char c : line) {
            if (isalpha(c)) {
                word += c;
            } else {
                if (!word.empty()) {
                    if (wordMap.find(word) != wordMap.end()) {
                        auto it = wordMap[word];
                        int index = distance(wordList.begin(), it) + 1;
                        cout << index;
                        wordList.erase(it);
                        wordList.push_front(word);
                        wordMap[word] = wordList.begin();
                    } else {
                        wordList.push_front(word);
                        wordMap[word] = wordList.begin();
                        cout << word;
                    }
                    word.clear();
                }
                cout << c;
            }
        }
        if (!word.empty()) {
            if (wordMap.find(word) != wordMap.end()) {
                auto it = wordMap[word];
                int index = distance(wordList.begin(), it) + 1;
                cout << index;
                wordList.erase(it);
                wordList.push_front(word);
                wordMap[word] = wordList.begin();
            } else {
                wordList.push_front(word);
                wordMap[word] = wordList.begin();
                cout << word;
            }
        }
        cout << endl;
    }

    return 0;
}
