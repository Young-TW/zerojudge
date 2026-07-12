#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int get_val(const string& s) {
    switch (s[0]) {
        case 'A': return 0;
        case 'T': return 9;
        case 'J': return 10;
        case 'Q': return 11;
        case 'K': return 12;
        default: return s[0] - '2' + 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string card;
    while (cin >> card) {
        if (card == "#") break;

        vector<string> cards(52);
        cards[0] = card;
        for (int i = 1; i < 52; ++i) {
            cin >> cards[i];
        }

        vector<string> piles[13];
        for (int i = 0; i < 52; ++i) {
            piles[i % 13].push_back(cards[51 - i]);
        }

        string current_card = piles[12].back();
        piles[12].pop_back();
        int exposed = 1;
        int val = get_val(current_card);

        while (!piles[val].empty()) {
            current_card = piles[val].back();
            piles[val].pop_back();
            exposed++;
            val = get_val(current_card);
        }

        cout << setw(2) << setfill('0') << exposed << "," << current_card << "\n";
    }

    return 0;
}
