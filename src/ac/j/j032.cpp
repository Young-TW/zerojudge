#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned int n;
    while (cin >> n && n) {
        unsigned int a = 0, b = 0;
        bool turn = true;
        
        for (int i = 0; i < 32; ++i) {
            if ((n >> i) & 1) {
                if (turn) {
                    a |= (1U << i);
                } else {
                    b |= (1U << i);
                }
                turn = !turn;
            }
        }
        
        cout << a << " " << b << "\n";
    }
    
    return 0;
}
