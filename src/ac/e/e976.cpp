#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long H, M, S;
    while (cin >> H >> M >> S) {
        cout << H << " " << M << " " << S << ". ";
        if (M <= H * S) {
            cout << "I will make it!\n";
        } else {
            cout << "I will be late!\n";
        }
    }
    
    return 0;
}
