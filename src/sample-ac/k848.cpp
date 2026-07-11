#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Card {
    int a, b, c;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<Card> cards;
        cards.reserve(N);
        int maxA = INT_MIN, maxB = INT_MIN, maxC = INT_MIN;
        
        for (int i = 0; i < N; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            cards.push_back({a, b, c});
            if (a > maxA) maxA = a;
            if (b > maxB) maxB = b;
            if (c > maxC) maxC = c;
        }
        
        int bestScore = -1;
        int bestIdx = -1;
        
        for (int i = 0; i < N; ++i) {
            int score = 0;
            if (cards[i].a == maxA) ++score;
            if (cards[i].b == maxB) ++score;
            if (cards[i].c == maxC) ++score;
            
            if (score > bestScore) {
                bestScore = score;
                bestIdx = i + 1;
            }
        }
        
        cout << bestIdx << '\n';
    }
    
    return 0;
}
