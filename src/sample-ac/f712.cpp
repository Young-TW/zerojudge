#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int rankVal(int id) {
    return (id % 13 + 12) % 13;
}

int suitVal(int id) {
    return 3 - id / 13;
}

char rankChar(int rv) {
    switch(rv) {
        case 12: return 'A';
        case 11: return 'K';
        case 10: return 'Q';
        case 9: return 'J';
        case 8: return 'T';
        default: return '0' + (rv + 2);
    }
}

char suitChar(int id) {
    switch(id / 13) {
        case 0: return 'S';
        case 1: return 'H';
        case 2: return 'D';
        default: return 'C';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; cas++) {
        vector<int> cards(52);
        for (int i = 0; i < 52; i++) cin >> cards[i];
        
        vector<vector<int>> hands(10);
        for (int i = 0; i < 50; i++) {
            hands[i % 10].push_back(cards[i]);
        }
        
        for (int p = 0; p < 10; p++) {
            sort(hands[p].begin(), hands[p].end(), [](int a, int b) {
                int ra = rankVal(a), rb = rankVal(b);
                if (ra != rb) return ra > rb;
                return suitVal(a) > suitVal(b);
            });
        }
        
        vector<int> order(10);
        for (int i = 0; i < 10; i++) order[i] = i;
        sort(order.begin(), order.end(), [&](int a, int b) {
            for (int i = 0; i < 5; i++) {
                int ra = rankVal(hands[a][i]), rb = rankVal(hands[b][i]);
                if (ra != rb) return ra > rb;
            }
            return suitVal(hands[a][0]) > suitVal(hands[b][0]);
        });
        
        cout << "Case " << cas << ":\n";
        for (int i = 0; i < 10; i++) {
            int p = order[i];
            cout << (p + 1);
            for (int j = 0; j < 5; j++) {
                cout << ' ' << suitChar(hands[p][j]) << rankChar(rankVal(hands[p][j]));
            }
            cout << '\n';
        }
    }
    return 0;
}
