#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void processWord(const string& word) {
    if (word.empty()) return;
    if (isVowel(word[0])) {
        cout << word << "ay";
    } else {
        cout << word.substr(1) << word[0] << "ay";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    char c;
    string word;
    
    while (cin.get(c)) {
        if (isalpha(c)) {
            word += c;
        } else {
            processWord(word);
            word.clear();
            cout << c;
        }
    }
    processWord(word);
    
    return 0;
}
