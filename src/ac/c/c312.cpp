#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    while (cin >> n >> k) {
        int survivor = 0;
        for (int i = 2; i <= n; ++i) {
            survivor = (survivor + k) % i;
        }
        cout << survivor + 1 << '\n';
    }
    
    return 0;
}
