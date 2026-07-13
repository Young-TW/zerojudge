#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int K, E;
    int setNum = 0;
    while (cin >> K >> E) {
        setNum++;
        cin.ignore();
        set<string> keywords;
        for (int i = 0; i < K; i++) {
            string kw;
            getline(cin, kw);
            keywords.insert(kw);
        }
        vector<string> excuses(E);
        vector<int> counts(E, 0);
        int maxCount = 0;
        for (int i = 0; i < E; i++) {
            string line;
            getline(cin, line);
            excuses[i] = line;
            string word;
            int cnt = 0;
            for (size_t j = 0; j <= line.size(); j++) {
                char c = (j < line.size()) ? line[j] : ' ';
                if (isalpha((unsigned char)c)) {
                    word += (char)tolower((unsigned char)c);
                } else {
                    if (!word.empty()) {
                        if (keywords.count(word)) cnt++;
                        word.clear();
                    }
                }
            }
            counts[i] = cnt;
            if (cnt > maxCount) maxCount = cnt;
        }
        cout << "Excuse Set #" << setNum << "\n";
        for (int i = 0; i < E; i++) {
            if (counts[i] == maxCount) {
                cout << excuses[i] << "\n";
            }
        }
        cout << "\n";
    }
    return 0;
}
