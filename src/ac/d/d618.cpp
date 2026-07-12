#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            int curr = 1;
            for (size_t i = 0; i < s.length(); ++i) {
                int next = s[i] - '0';
                bool valid = false;
                if (curr == 2) {
                    if (next == 1) valid = true;
                } else if (curr == 3 || curr == 4) {
                    if (next == 1 || next == 3 || next == 4) valid = true;
                } else {
                    valid = true;
                }
                if (valid) {
                    curr = next;
                }
            }
            cout << curr << "\n";
        }
    }
    return 0;
}
