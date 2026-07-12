#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    
    long long total = 0;
    for (int i = 0; i < T; ++i) {
        string op;
        cin >> op;
        if (op == "donate") {
            long long K;
            cin >> K;
            total += K;
        } else if (op == "report") {
            cout << total << "\n";
        }
    }
    
    return 0;
}
