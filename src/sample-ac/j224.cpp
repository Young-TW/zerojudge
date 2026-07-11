#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        bool seen[926] = {false};
        int count = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (!seen[x]) {
                seen[x] = true;
                count++;
            }
        }
        cout << count << "\n";
    }
    
    return 0;
}
