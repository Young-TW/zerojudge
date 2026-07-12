#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long L;
    while (cin >> L) {
        long long H = L / 2;
        long long S = (H / 2) * ((H + 1) / 2);
        cout << S << "\n";
    }
    
    return 0;
}
