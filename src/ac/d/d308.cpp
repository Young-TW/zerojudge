#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string n;
    long long m;
    while (cin >> n >> m) {
        long long ans = 0;
        for (size_t i = 0; i < n.size(); ++i) {
            ans = (ans * 10 + (n[i] - '0')) % m;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
