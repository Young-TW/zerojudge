#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int getCardValue(const string& card) {
    string suits = "CDSH";
    string ranks = "23456789TJQKA";
    return suits.find(card[0]) * 13 + ranks.find(card[1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    char dealerChar;
    while (cin >> dealerChar && dealerChar != '#') {
        int dealer;
        switch (dealerChar) {
            case 'N': dealer = 0; break;
            case 'E': dealer = 1; break;
            case 'S': dealer = 2; break;
            case 'W': dealer = 3; break;
        }
        
        string line1, line2;
        cin >> line1 >> line2;
        string deck = line1 + line2;
        
        vector<vector<string>> hands(4);
        
        for (int i = 0; i < 52; ++i) {
            string card = deck.substr(i * 2, 2);
            int player = (dealer + 1 + i) % 4;
            hands[player].push_back(card);
        }
        
        for (int i = 0; i < 4; ++i) {
            sort(hands[i].begin(), hands[i].end(), [](const string& a, const string& b) {
                return getCardValue(a) < getCardValue(b);
            });
        }
        
        string players[] = {"S", "W", "N", "E"};
        int order[] = {2, 3, 0, 1};
        for (int i = 0; i < 4; ++i) {
            cout << players[i] << ":";
            for (const string& card : hands[order[i]]) {
                cout << " " << card;
            }
            cout << "\n";
        }
    }
    
    return 0;
}
