#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<string> words;
    string word;
    while (cin >> word) {
        words.push_back(word);
    }
    
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << words[i] << " little";
        if (i == words.size() - 1) {
            cout << " Indians";
        } else {
            cout << ",";
        }
    }
    cout << "\n";
    
    return 0;
}
