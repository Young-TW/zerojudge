#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line == "END") break;
        
        stringstream ss(line);
        string word;
        vector<string> words;
        while (ss >> word) {
            words.push_back(word);
        }
        
        if (words.empty()) continue;
        
        string acronym;
        for (size_t i = 0; i < words.size(); ++i) {
            acronym += static_cast<char>(toupper(static_cast<unsigned char>(words[i][0])));
        }
        
        cout << acronym << " " << words.back() << "\n";
    }
    
    return 0;
}
