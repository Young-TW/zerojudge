#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        while (n--) {
            int f;
            cin >> f;
            long long total = 0;
            for (int i = 0; i < f; ++i) {
                long long area, animals, level;
                cin >> area >> animals >> level;
                total += area * level;
            }
            cout << total << "\n";
        }
    }
    
    return 0;
}
