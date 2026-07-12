#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long limit = 9;
        bool stan_turn = true;
        
        while (n > limit) {
            stan_turn = !stan_turn;
            if (stan_turn) {
                limit *= 9;
            } else {
                limit *= 2;
            }
        }
        
        if (stan_turn) {
            cout << "Stan wins.\n";
        } else {
            cout << "Ollie wins.\n";
        }
    }
    
    return 0;
}
