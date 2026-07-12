#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int parseVal(char v) {
    if (v == 'A') return 1;
    if (v >= '2' && v <= '9') return v - '0';
    if (v == 'T') return 10;
    if (v == 'J') return 11;
    if (v == 'Q') return 12;
    return 13;
}

int parseSuit(char s) {
    if (s == 'C') return 0;
    if (s == 'D') return 1;
    if (s == 'H') return 2;
    return 3;
}

bool isPlayable(const string& card, int low[], int high[], bool sevenPlayed[]) {
    int val = parseVal(card[0]);
    int suit = parseSuit(card[1]);
    if (val == 7) return !sevenPlayed[suit];
    if (!sevenPlayed[suit]) return false;
    return val == low[suit] - 1 || val == high[suit] + 1;
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<string> cards(n);
        int coverCount = 0;
        for (int i = 0; i < n; i++) {
            cin >> cards[i];
            if (cards[i] == "XX") coverCount++;
        }
        vector<string> covers(coverCount);
        for (int i = 0; i < coverCount; i++) {
            cin >> covers[i];
        }
        
        vector<int> coverIndex(n, -1);
        int cidx = 0;
        for (int i = 0; i < n; i++) {
            if (cards[i] == "XX") {
                coverIndex[i] = cidx++;
            }
        }
        
        int cheater = -1;
        
        for (int i = 0; i < n && cheater == -1; i++) {
            if (cards[i] != "XX") continue;
            
            int player = (i % 4) + 1;
            
            int low[4], high[4];
            bool sevenPlayed[4] = {false, false, false, false};
            for (int s = 0; s < 4; s++) { low[s] = 7; high[s] = 7; }
            
            for (int j = 0; j < i; j++) {
                if (cards[j] == "XX") continue;
                int val = parseVal(cards[j][0]);
                int suit = parseSuit(cards[j][1]);
                if (val == 7) {
                    sevenPlayed[suit] = true;
                    low[suit] = high[suit] = 7;
                } else if (val < 7) {
                    low[suit] = min(low[suit], val);
                } else {
                    high[suit] = max(high[suit], val);
                }
            }
            
            vector<string> hand;
            hand.push_back(covers[coverIndex[i]]);
            for (int j = i + 1; j < n; j++) {
                if ((j % 4) + 1 != player) continue;
                if (cards[j] == "XX") {
                    hand.push_back(covers[coverIndex[j]]);
                } else {
                    hand.push_back(cards[j]);
                }
            }
            
            for (size_t k = 0; k < hand.size(); k++) {
                if (isPlayable(hand[k], low, high, sevenPlayed)) {
                    cheater = player;
                    break;
                }
            }
        }
        
        if (cheater == -1) {
            cout << "No one cheated!" << endl;
        } else {
            cout << cheater << " cheated!" << endl;
        }
    }
    return 0;
}
