#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        int sum = 0;
        int dir = 1; // 1 = CW, -1 = CCW
        int cur = 1;
        bool cheated = false;
        int cheater = -1;
        
        for (int i = 0; i < m; i++) {
            string card;
            cin >> card;
            if (cheated) continue;
            
            int player = cur;
            
            if (card == "A") {
                sum = 0;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "2") {
                sum += 2;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "3") {
                sum += 3;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "4") {
                dir = -dir;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card[0] == '5') {
                int x = stoi(card.substr(2, card.size() - 3));
                cur = x;
            } else if (card == "6") {
                sum += 6;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "7") {
                sum += 7;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "8") {
                sum += 8;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "9") {
                sum += 9;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "10+") {
                sum += 10;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "10-") {
                sum = max(0, sum - 10);
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "J") {
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "Q+") {
                sum += 20;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "Q-") {
                sum = max(0, sum - 20);
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            } else if (card == "K") {
                sum = 99;
                cur = ((cur - 1 + dir) % n + n) % n + 1;
            }
            
            if (sum > 99) {
                cheated = true;
                cheater = player;
            }
        }
        
        if (cheated) {
            cout << cheater << " cheated!" << endl;
        } else {
            cout << "The sum is " << sum << endl;
        }
    }
    return 0;
}
