#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string word, article;
    bool first = true;
    while (getline(cin, word)) {
        if (!word.empty() && word.back() == '\r') word.pop_back();
        if (word.empty()) continue;
        getline(cin, article);
        if (!article.empty() && article.back() == '\r') article.pop_back();

        string wlower = word;
        for (auto &c : wlower) c = (char)tolower(c);

        int count = 0, firstPos = -1;
        int n = (int)article.size();
        int i = 0;
        while (i < n) {
            while (i < n && article[i] == ' ') i++;
            if (i >= n) break;
            int start = i;
            string cur;
            while (i < n && article[i] != ' ') {
                cur += (char)tolower(article[i]);
                i++;
            }
            if (cur == wlower) {
                count++;
                if (firstPos == -1) firstPos = start;
            }
        }

        if (!first) cout << "\n";
        first = false;
        if (count > 0) cout << count << " " << firstPos << "\n";
        else cout << -1 << "\n";
    }
    return 0;
}
