#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

bool match(const string& a, const string& b) {
    return a[0] == b[0] || a[1] == b[1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string card;
    while (cin >> card) {
        if (card == "#") break;
        
        vector<stack<string>> piles;
        stack<string> s;
        s.push(card);
        piles.push_back(s);
        
        for (int i = 1; i < 52; ++i) {
            cin >> card;
            stack<string> temp;
            temp.push(card);
            piles.push_back(temp);
        }
        
        bool moved = true;
        while (moved) {
            moved = false;
            for (int i = 0; i < (int)piles.size(); ++i) {
                string top_card = piles[i].top();
                int target = -1;
                
                if (i >= 3 && match(top_card, piles[i-3].top())) {
                    target = i - 3;
                } else if (i >= 1 && match(top_card, piles[i-1].top())) {
                    target = i - 1;
                }
                
                if (target != -1) {
                    piles[target].push(top_card);
                    piles[i].pop();
                    if (piles[i].empty()) {
                        piles.erase(piles.begin() + i);
                    }
                    moved = true;
                    break;
                }
            }
        }
        
        cout << piles.size() << " pile" << (piles.size() == 1 ? "" : "s") << " remaining:";
        for (size_t i = 0; i < piles.size(); ++i) {
            cout << " " << piles[i].size();
        }
        cout << "\n";
    }
    
    return 0;
}
