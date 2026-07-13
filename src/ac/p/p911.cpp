#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string card;
    while (cin >> card) {
        int count[4] = {0};
        int points = 0;
        
        for (int i = 0; i < 13; ++i) {
            if (i > 0) {
                if (!(cin >> card)) break;
            }
            
            char suit = card[0];
            string rank = card.substr(1);
            
            if (suit == 'S') count[0]++;
            else if (suit == 'H') count[1]++;
            else if (suit == 'D') count[2]++;
            else if (suit == 'C') count[3]++;
            
            if (rank == "A") points += 4;
            else if (rank == "K") points += 3;
            else if (rank == "Q") points += 2;
            else if (rank == "J") points += 1;
        }
        
        cout << count[0] << " " << count[1] << " " << count[2] << " " << count[3] << "\n";
        cout << points << "\n";
    }
    
    return 0;
}
