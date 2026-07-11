#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int getRank(char c) {
    if (c == 'A') return 0;
    if (c >= '2' && c <= '9') return c - '1';
    if (c == 'T') return 9;
    if (c == 'J') return 10;
    if (c == 'Q') return 11;
    if (c == 'K') return 12;
    return -1;
}

int getSuitRank(char c) {
    if (c == 'C') return 0;
    if (c == 'D') return 1;
    if (c == 'H') return 2;
    if (c == 'S') return 3;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n != 0) {
        vector<string> cards[13];
        int joker_count = 0;
        
        for (int i = 0; i < n; ++i) {
            string card;
            cin >> card;
            if (card == "GG") {
                joker_count++;
            } else {
                int r = getRank(card[0]);
                if (r >= 0 && r < 13) {
                    cards[r].push_back(card);
                }
            }
        }
        
        vector<string> result;
        for (int i = 0; i < 13; ++i) {
            if (!cards[i].empty()) {
                sort(cards[i].begin(), cards[i].end(), [](const string& a, const string& b) {
                    return getSuitRank(a[1]) < getSuitRank(b[1]);
                });
                if (cards[i].size() % 2 == 1) {
                    result.push_back(cards[i].back());
                }
            }
        }
        
        for (int i = 0; i < joker_count; ++i) {
            result.push_back("GG");
        }
        
        if (result.empty()) {
            cout << "No card\n";
        } else {
            for (const string& c : result) {
                cout << c << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
