#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    while (cin >> n >> k) {
        vector<string> cards(n);
        for (int i = 0; i < n; ++i) {
            cin >> cards[i];
        }
        rotate(cards.begin(), cards.begin() + k, cards.end());
        for (int i = 0; i < n; ++i) {
            cout << cards[i] << "\n";
        }
    }
    
    return 0;
}
