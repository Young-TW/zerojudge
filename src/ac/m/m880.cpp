#include <iostream>
#include <string>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string cards[14];
    while (cin >> cards[0]) {
        for (int i = 1; i < 14; ++i) {
            cin >> cards[i];
        }
        
        int N;
        cin >> N;
        for (int i = 0; i < N; ++i) {
            int a, b;
            cin >> a >> b;
            swap(cards[a], cards[b]);
        }
        
        int pos[14];
        for (int i = 0; i < 14; ++i) {
            cin >> pos[i];
        }
        
        for (int i = 0; i < 14; ++i) {
            cout << cards[i];
            if (i < 13) {
                cout << " ";
            }
        }
        cout << "\n";
        
        for (int i = 0; i < 14; ++i) {
            if (cards[pos[i]] == "Joker") {
                cout << (i + 1) << "\n";
                break;
            }
        }
    }
    
    return 0;
}
