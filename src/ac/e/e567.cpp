#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            vector<int> ops(n + 1, 0);
            int pos = 0;
            for (int i = 1; i <= n; ++i) {
                string cmd;
                cin >> cmd;
                if (cmd == "LEFT") {
                    ops[i] = -1;
                    pos += ops[i];
                } else if (cmd == "RIGHT") {
                    ops[i] = 1;
                    pos += ops[i];
                } else {
                    string as;
                    int idx;
                    cin >> as >> idx;
                    ops[i] = ops[idx];
                    pos += ops[i];
                }
            }
            cout << pos << "\n";
        }
    }
    
    return 0;
}
