#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <cctype>
using namespace std;

bool isSubseq(const string& abbr, const string& word) {
    size_t i = 0;
    for (size_t j = 0; j < word.size() && i < abbr.size(); j++) {
        if (abbr[i] == word[j]) i++;
    }
    return i == abbr.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    stringstream ss;
    ss << cin.rdbuf();
    string all = ss.str();
    
    size_t bar = all.find('|');
    if (bar == string::npos) return 0;
    
    string dictPart = all.substr(0, bar);
    
    size_t start = bar + 1;
    while (start < all.size() && (all[start] == ' ' || all[start] == '\t')) start++;
    string textPart = all.substr(start);
    
    vector<string> dict;
    stringstream ds(dictPart);
    string t;
    while (ds >> t) dict.push_back(t);
    
    string result;
    size_t i = 0;
    while (i < textPart.size()) {
        if (isalpha((unsigned char)textPart[i])) {
            string w;
            while (i < textPart.size() && isalpha((unsigned char)textPart[i])) {
                w += textPart[i];
                i++;
            }
            string best;
            int bestLen = INT_MAX;
            int bestCount = 0;
            for (size_t k = 0; k < dict.size(); k++) {
                if (isSubseq(w, dict[k])) {
                    int added = (int)dict[k].size() - (int)w.size();
                    if (added < bestLen) {
                        bestLen = added;
                        best = dict[k];
                        bestCount = 1;
                    } else if (added == bestLen) {
                        bestCount++;
                    }
                }
            }
            if (bestCount == 1) result += best;
            else result += w;
        } else {
            result += textPart[i];
            i++;
        }
    }
    cout << result;
    return 0;
}
