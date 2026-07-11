#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<string> cards(n);
        for (int i = 0; i < n; ++i) {
            cin >> cards[i];
        }
        int k;
        cin >> k;
        
        for (int i = k; i < n; ++i) {
            if (i > k) cout << " ";
            cout << cards[i];
        }
        for (int i = 0; i < k; ++i) {
            cout << " " << cards[i];
        }
        cout << "\n";
    }
    
    return 0;
}
