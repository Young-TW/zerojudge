#include <iostream>

using namespace std;

int seen[2000001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    int token = 0;
    while (cin >> n) {
        token++;
        bool first = true;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            int idx = x + 1000000;
            if (seen[idx] != token) {
                seen[idx] = token;
                if (!first) {
                    cout << ' ';
                }
                cout << x;
                first = false;
            }
        }
        cout << '\n';
    }
    
    return 0;
}
