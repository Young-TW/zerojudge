#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string word;
    vector<string> words;
    map<string, int> count;
    
    while (cin >> word && word != "#") {
        words.push_back(word);
        string normalized = word;
        for (size_t i = 0; i < normalized.size(); ++i) {
            normalized[i] = tolower((unsigned char)normalized[i]);
        }
        sort(normalized.begin(), normalized.end());
        count[normalized]++;
    }
    
    vector<string> ananagrams;
    for (size_t i = 0; i < words.size(); ++i) {
        const string& w = words[i];
        string normalized = w;
        for (size_t j = 0; j < normalized.size(); ++j) {
            normalized[j] = tolower((unsigned char)normalized[j]);
        }
        sort(normalized.begin(), normalized.end());
        if (count[normalized] == 1) {
            ananagrams.push_back(w);
        }
    }
    
    sort(ananagrams.begin(), ananagrams.end());
    
    for (size_t i = 0; i < ananagrams.size(); ++i) {
        cout << ananagrams[i] << "\n";
    }
    
    return 0;
}
