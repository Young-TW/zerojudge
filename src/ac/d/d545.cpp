#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Card {
    int num;
    int suit_rank;
    char suit_char;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<Card> cards(N);
        for (int i = 0; i < N; ++i) {
            char s;
            int n;
            cin >> s >> n;
            cards[i].suit_char = s;
            cards[i].num = n;
            if (s == 'S') cards[i].suit_rank = 4;
            else if (s == 'H') cards[i].suit_rank = 3;
            else if (s == 'D') cards[i].suit_rank = 2;
            else if (s == 'C') cards[i].suit_rank = 1;
        }
        int M;
        cin >> M;
        
        nth_element(cards.begin(), cards.begin() + M - 1, cards.end(), [](const Card& a, const Card& b) {
            if (a.num != b.num) return a.num > b.num;
            return a.suit_rank > b.suit_rank;
        });
        
        cout << cards[M - 1].suit_char << " " << cards[M - 1].num << "\n";
    }
    
    return 0;
}
