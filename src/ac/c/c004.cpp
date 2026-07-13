#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        while (n--) {
            long long s, d;
            cin >> s >> d;
            if (s < d || (s + d) % 2 != 0) {
                cout << "impossible\n";
            } else {
                long long x = (s + d) / 2;
                long long y = (s - d) / 2;
                cout << x << " " << y << "\n";
            }
        }
    }
    
    return 0;
}
