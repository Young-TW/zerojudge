#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            int O = 0, E = 0;
            for (int i = 0; i < n; ++i) {
                string card;
                cin >> card;
                int val = 0;
                if (card[0] == 'A') val = 1;
                else if (card[0] == 'T') val = 10;
                else if (card[0] == 'J') val = 11;
                else if (card[0] == 'Q') val = 12;
                else if (card[0] == 'K') val = 13;
                else val = card[0] - '0';
                
                if (val % 2 == 1) O++;
                else E++;
            }
            
            if (E <= 1) {
                if (O % 2 == 0) cout << "P\n";
                else cout << "N\n";
            } else if (E <= 3) {
                if (O % 2 == 0) cout << "N\n";
                else cout << "P\n";
            } else {
                cout << "N\n";
            }
        }
    }
    
    return 0;
}
