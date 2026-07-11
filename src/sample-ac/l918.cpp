#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long X, Y, N;
    while (cin >> X >> Y >> N) {
        long long total = 0;
        if (X > 0) {
            if (Y == 1) {
                total = N;
            } else {
                total = X + (X - 1) / (Y - 1);
            }
        }
        
        if (total >= N) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
